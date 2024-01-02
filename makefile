CXX = g++
CCFLAGS = -std=c++17

BASEDIR = src
OBJ_DIR = obj
OUTPUTDIR = dist
TARGET = convert

DEBUG_ARGS = -a 1 -d
ARGS = -a 2

SRCS := $(wildcard $(BASEDIR)/*.cpp $(BASEDIR)/**/*.cpp)
OBJS := $(patsubst $(BASEDIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
INC_DIRS := $(shell find $(BASEDIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

ifeq ($(OS),Windows_NT)
    TARGET = convert.exe
	CCFLAGS += -D WIN32
else
    TARGET = convert
	CCFLAGS += -D LINUX
endif

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(BASEDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CCFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET) $(DEBUG_ARGS)

debug: $(TARGET)
	./$(TARGET) $(DEBUG_ARGS)

run: $(TARGET)
	./$(TARGET) $(ARGS)