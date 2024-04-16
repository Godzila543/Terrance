# Compiler
CXX = g++

# Directories
SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./.obj

# Compiler flags
CXXFLAGS = -I$(INC_DIR)

# Find all C++ files in the src directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = main 

# Default rule
all: $(TARGET)

# Rule to link the target
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ -lpigpio

# Rule to compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
