CXX=g++
OS := $(shell uname)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g
CXXFLAGS += -I ./include/vector
CXXFLAGS += -I ./include/stack
CXXFLAGS += -I ./include/map
CXXFLAGS += -I ./include/set

ifeq ($(OS),Linux)
	CXXFLAGS += -DLINUX
endif


SRCS=main.cpp
OBJECTS=$(patsubst %.cpp, %.o, $(SRCS))
NAME=ft_container

OS := $(shell uname)

all:$(NAME)

$(NAME) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -v -o $@ $^

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -rf $(OBJECTS)

fclean:
	make clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: clean fclean re bonus


