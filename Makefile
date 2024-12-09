# Compiler to use
CC = clang

# Compliler flags
CFLAGS = -Wall -g -Iinclude

# Target executable
TARGET = dfs

# Linker flags to include libfuse3
LDFLAGS = -lfuse3

# Its the include (for .h files), src (for .c files) and build (for .o files and executable)
INCLUDE = include/*.h
SRCS = src/*.c
BUILD = build

# Object files (in the build directory)
OBJS = $(SRCS:src/%.c=build/%.o)

# Default arguments (empty by default)
ARGS = 

# Default target to build and run all executable
all: $(BUILD) $(BUILD)/$(TARGET)
	@echo "Running the executable with arguments: $(ARGS)"
	@./$(BUILD)/$(TARGET) $(ARGS)

# Create a build directory if it doesn't exist 
$(BUILD):
	mkdir -p $(BUILD)

# Link object files to create the executable in the build directory
$(BUILD)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compiles .c files into .o files in the directory
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build artifacts
clean:
	rm -rf $(BUILD)

# Phony targets to avoid all conflicts with file names
.PHONY: all clean
