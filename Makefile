TARGET_EXEC = mcp_app

BUILD_DIR = ./build
SRC_DIRS = ./src

CC = gcc
CXX = g++

SRCS = $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS = $(shell find $(SRC_DIRS) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CFLAGS = $(INC_FLAGS) -std=gnu99
CPPFLAGS = $(INC_FLAGS) -std=gnu++11

LDLIBS = -ludev

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CPPFLAGS) $(LDLIBS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) -c -o $@ $< $(CPPFLAGS)


.PHONY: clean

clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
