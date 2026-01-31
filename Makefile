# Toolchain definition
GNU_PREFIX = arm-none-eabi-
CC = $(GNU_PREFIX)gcc
LD = $(GNU_PREFIX)gcc
SZ = $(GNU_PREFIX)size
DUMP = $(GNU_PREFIX)objdump

# Directories
BSP_DIR = lm3s6965
BUILD_DIR = Build

# Target file name (stored in Build directory)
TARGET = $(BUILD_DIR)/main

# Linker Script path
LDSCRIPT = $(BSP_DIR)/lm3s6965.ld

# Source files
# main.c is in the root, startup is in the BSP directory
SRCS = main.c $(BSP_DIR)/startup_lm3s6965.c

# Object files
# 1. $(SRCS:.c=.o) -> changes .c extension to .o (e.g., main.o lm3s6965/startup_lm3s6965.o)
# 2. $(notdir ...) -> removes directory paths (e.g., main.o startup_lm3s6965.o)
# 3. $(addprefix ...) -> adds Build/ prefix (e.g., Build/main.o Build/startup_lm3s6965.o)
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.c=.o)))

# VPATH: Where to look for source files if they are not in the current directory
vpath %.c . $(BSP_DIR)

# Flags
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall --specs=rdimon.specs
LDFLAGS = -mcpu=cortex-m3 -mthumb -T $(LDSCRIPT) --specs=rdimon.specs -Wl,-Map=$(TARGET).map -Wl,--gc-sections -lc -lrdimon

ifeq ($(OS), Windows_NT)
# Windows Settings
MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
RM = if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
CLEAR = cls
else
# Linux / Unix / macOS Settings
MKDIR = mkdir -p $(BUILD_DIR)
RM = rm -rf $(BUILD_DIR)
CLEAR = clear
endif

# Default target
all: $(BUILD_DIR) $(TARGET).elf $(TARGET).dump

# Rule to create the Build directory
$(BUILD_DIR):
	$(MKDIR)

# Compile
# Using VPATH, make finds the .c file. We output the .o to BUILD_DIR.
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
	$(SZ) $@

$(TARGET).dump: $(TARGET).elf
	$(DUMP) -D -S $< > $@

# Clean
clean:
	$(RM)

# Run QEMU
run: all
	@$(CLEAR)
	@qemu-system-arm -M lm3s6965evb -semihosting-config enable=on,target=native -nographic -kernel $(TARGET).elf
