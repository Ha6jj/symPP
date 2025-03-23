CXX = g++
 
CXXFLAGS = -Wall -std=c++17 -O2 -MMD
 
SRC_DIR = src
DB_DIR = $(SRC_DIR)/baseExpression
BUILD_DIR = ./build
 
SRCS = main.cpp \
$(SRC_DIR)/expression.cpp \
$(SRC_DIR)/lexer.cpp \
$(SRC_DIR)/parser.cpp \
$(DB_DIR)/constant.cpp \
$(DB_DIR)/cos.cpp \
$(DB_DIR)/div.cpp \
$(DB_DIR)/exp.cpp \
$(DB_DIR)/ln.cpp \
$(DB_DIR)/pow.cpp \
$(DB_DIR)/prod.cpp \
$(DB_DIR)/sin.cpp \
$(DB_DIR)/sub.cpp \
$(DB_DIR)/sum.cpp \
$(DB_DIR)/symbol.cpp
 
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))
 
TARGET = main
 
DEPS = $(OBJS:.o=.d)
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
 
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
$(BUILD_DIR)/$(SRC_DIR)/expression.o: $(SRC_DIR)/expression.cpp $(SRC_DIR)/lexer.hpp $(DB_DIR)/baseExpression.hpp
 
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
 
run: $(TARGET)
	./$(TARGET)
 
rebuild: clean all
 
-include $(DEPS)
 
.PHONY: all clean run rebuild