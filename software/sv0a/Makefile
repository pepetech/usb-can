TARGET = mcp_app

BUILD = ./build
SRC = ./src

CC = gcc
CXX = g++

CFLAGS = $(INC_FLAGS) -std=gnu99
CPPFLAGS = $(INC_FLAGS) -std=gnu++11

LDLIBS = -ludev

SRCS = $(shell find $(SRC) -name *.cpp -or -name *.c)
OBJS = $(SRCS:%=$(BUILD)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS = $(shell find $(SRC) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

$(BUILD)/$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(CPPFLAGS) $(LDLIBS)

# c source
$(BUILD)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

# c++ source
$(BUILD)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) -c -o $@ $< $(CPPFLAGS)


.PHONY: clean

clean:
	rm -r $(BUILD)

-include $(DEPS)

MKDIR_P ?= mkdir -p
