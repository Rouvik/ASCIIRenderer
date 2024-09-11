# PHONY targets
.PHONY: all mkdirs clean

# Directories
SRC := ./Engine
BUILD := ./build

# Targets to build
TARGETS = $(wildcard $(SRC)/*.c)
TARGET_OBJS = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(TARGETS))

# Define the compiler as GCC
CC := gcc

# Debug
DEBUG := -ggdb

all: mkdirs main.c $(TARGET_OBJS)
	$(CC) main.c $(TARGET_OBJS) -o $(BUILD)/main.exe $(DEBUG)

$(BUILD)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) -c $< -o $@ $(DEBUG)

mkdirs:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)