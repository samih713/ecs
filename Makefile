RM:= rm -rf

NAME:=geometry_wars
CXX:=g++
CXXFLAGS:=-Wall -Wextra -Werror -MMD -MP -ggdb3

SRCS_DIR:=srcs
SRCS:=$(wildcard $(SRCS_DIR)/*.cpp)

BUILD_DIR:=build
OBJS:=$(patsubst $(SRCS_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
DEPS:=$(patsubst %.o, %.d, $(OBJS))

LIBS:=-lraylib
INCLUDES:=-I./include

MAIN:=main.cpp

all: $(NAME)

run: all
	./$(BUILD_DIR)/$(NAME)

$(NAME): $(OBJS) | $(BUILD_DIR) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(MAIN) $(LIBS) -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	@mkdir $@

clean:
	@$(RM) $(BUILD_DIR)

-include $(DEPS)