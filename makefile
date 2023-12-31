CXX := g++

BASEDIR := src
OBJ_DIR := obj
OUTPUTDIR := dist
TARGET := convert

CCFLAGS := -std=c++17

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

run: $(TARGET)
	./$(TARGET)