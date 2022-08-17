TARGET		:= webserv
CXX			:= g++
CXXFLAGS	:= -pedantic-errors -Wall -Wextra -Werror -std=c++98 -pedantic -fdiagnostics-color=always
LDFLAGS		:= -L/usr/lib -lstdc++ -lm
OBJ_DIR		:= ./objects
APP_DIR		:= ./
INC_DIRS	:= $(shell find ./include -type d)
INCLUDE		:= $(addprefix -I,$(INC_DIRS))
SRC			:= $(wildcard srcs/*.cpp)

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

debug: CXXFLAGS += -g
debug: fclean all

release: CXXFLAGS += -O2
release: fclean all

clean:
	rm -rvf $(OBJ_DIR)/*

fclean: clean
	rm -rf $(TARGET)

re: clean all

test: debug
	./webserv config/default.conf
