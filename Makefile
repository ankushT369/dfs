# Compiler to use
CC = clang

# Compiler flags
CFLAGS = -Wall -g -Iinclude

# Target executable
TARGET = dfs

# Linker flags to include libfuse3
LDFLAGS = -lfuse3

# Include directory for headers
INCLUDE = include/*.h

# Source files
SRCS = src/dfs.c src/util.c

# Build directory
BUILD = build

# Object files (in the build directory)
OBJS = $(SRCS:src/%.c=$(BUILD)/%.o)

# Default target to build only
all: $(BUILD) $(BUILD)/$(TARGET)

# Create a build directory if it doesn't exist 
$(BUILD):
	mkdir -p $(BUILD)

# Link object files to create the executable in the build directory
$(BUILD)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compiles .c files into .o files in the build directory
$(BUILD)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build artifacts
clean:
	rm -rf $(BUILD)

# Phony targets to avoid all conflicts with file names
.PHONY: all clean

