NAME = vector_test

CXX = c++
# -std=c++98
#
CXXFLAGS = -Wall \
		   -Werror \
		   -Wextra \
		   -Wshadow \
		   -std=c++98 \
		   -pedantic \
		   $(INCS) \
		   $(NULL)

INCDIR = ./includes \
		  $(NULL)
INCS = $(addprefix -I, $(INCDIR))

TESTDIR	= ./tests
VECTOR_SRCS = $(shell find $(TESTDIR) -name '*.cpp')

OBJDIR	= ./objs
VECTOR_OBJS = $(addprefix $(OBJDIR)/, $(notdir $(VECTOR_SRCS:.cpp=.o)))

DEPS = $(VECTOR_OBJS:.o=.d)

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJDIR) $(VECTOR_OBJS)
	$(CXX) $(CXXFLAGS) $(VECTOR_OBJS) -o $@

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o : $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

.PHONY: run
run: $(NAME)
	./$(NAME)

.PHONY: sketch
sketch:
	$(CXX) sketch/main.cpp
	./a.out

.PHONY: clean
clean:
	$(RM) $(VECTOR_OBJS) $(DEPS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
