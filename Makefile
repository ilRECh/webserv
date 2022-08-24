TARGET		:= webserv
CXX			:= g++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -fdiagnostics-color=always $(CMDFLAGS)
LDFLAGS		:= -L/usr/lib -lstdc++ -lm
OBJ_DIR		:= ./objects
APP_DIR		:= ./
INC_DIRS	:= $(shell find ./include -type d)
INCLUDE		:= $(addprefix -I,$(INC_DIRS))
SRC			:= $(shell find srcs -type "f" -name "*.cpp") $(CMDSRC)

OBJECTS		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all build clean fclean debug release re test

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -g -D DEBUG_OUTPUT
debug: all

release: CXXFLAGS += -O2
release: fclean all

clean:
	rm -rvf $(OBJ_DIR)/*

fclean: clean
	rm -rf $(TARGET)

re: clean all
