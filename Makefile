######################################
# target
######################################
TARGET = freertos


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = bin


######################################
# source
######################################
# C sources
C_SOURCES_PATH = \
.	\
Src	\
Lib/STM32F10x_Driver/Src \
Lib/CMSIS/Device/ST/STM32F1xx/Source \
FreeRTOS \
FreeRTOS/portable \

C_SOURCES = $(foreach dir,$(C_SOURCES_PATH),$(wildcard $(dir)/*.c))


# ASM sources
ASM_SOURCES =  \
Lib\CMSIS\Device\ST\STM32F1xx\Source\startup_stm32f103c8tx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS = \
-DUSE_STDPERIPH_DRIVER \
-DSTM32F10X_MD


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES_PATH = \
Inc \
Lib/CMSIS/Device/ST/STM32F1xx/Include \
Lib/CMSIS/Include \
Lib/STM32F10x_Driver/Inc \
FreeRTOS/include \
FreeRTOS/portable \

C_INCLUDES = $(foreach dir,$(C_INCLUDES_PATH),-I$(dir)/)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2 -xc  -std=c11 
endif


# Generate dependency information
# CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CFLAGS += -MMD --specs=nosys.specs --specs=nano.specs 


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F103C8Tx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,--no-warn-rwx-segments,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -u_printf_float -u_fprintf_float 


# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects

OBJECTS = $(addprefix $(BUILD_DIR)/,$(C_SOURCES:.c=.o))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(ASM_SOURCES:.s=.o))
vpath %.s $(sort $(dir $(ASM_SOURCES)))
PAATH = $(BUILD_DIR)/$(C_SOURCES_PATH)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
# $(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)$(notdir $(<:.c=.lst)) $< -o $@
	$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(dir $<)$(notdir $@)

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $(BUILD_DIR)/$(dir $<)$(notdir $@)

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	@for item in $(C_SOURCES_PATH); do \
		mkdir -p $(BUILD_DIR)/$$item; \
	done

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***