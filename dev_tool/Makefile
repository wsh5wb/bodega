TARGET_EXEC ?= myGame
DEV_EXEC = devTool

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src/engine
DEV_DIRS ?= .

prod := 0

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
DEV_SRCS := $(shell find $(DEV_DIRS) -name *.cpp -or -name *.c -or -name *.s)

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEV_OBJS := $(DEV_SRCS:%=$(BUILD_DIR/%.o))

DEPS := $(OBJS:.o=.d)
DEV_DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17 -g 
CXX := g++-8

#LINKER_FLAGS specifies the libraries we're linking against
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lstdc++fs
FSAN_FLAGS = -fsanitize=address,leak

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

run:
	$(shell export ASAN_OPTIONS=new_delete_type_mismatch=0:alloc_dealloc_mismatch=0 && $(BUILD_DIR)/$(TARGET_EXEC)) || true

sanitize_setup:
	$(eval LDFLAGS += $(FSAN_FLAGS))
	$(eval CPPFLAGS += $(FSAN_FLAGS))

sanitize: sanitize_setup $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC) $(LDFLAGS)

dev_tool_setup:
	$(eval OBJS += $(DEV_OBJS))
	$(eval DEPS += $(DEV_DEPS))

dev_tool: dev_tool_setup $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD_DIR)/$(DEV_EXEC) $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@ 

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ -lstdc++fs

.PHONY: clean, sanitize, sanitize_setup, run, dev_tool, dev_tool_setup

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
