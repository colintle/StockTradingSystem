CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -g

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

# Output
TARGET := stock_trading

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

INCLUDE_PATHS := $(shell find $(INCLUDE_DIR) -type d)
CXXFLAGS += $(foreach dir, $(INCLUDE_PATHS), -I$(dir))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all clean rebuild
