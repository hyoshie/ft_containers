NAME_FT = test_ft
NAME_STL = test_stl

CXX = c++

CXXFLAGS = -Wall \
		   -Werror \
		   -Wextra \
		   -Wshadow \
		   -std=c++98 \
		   -pedantic \
		   -g \
		   $(INCS) \
		   $(NULL)

INCDIR = ./includes \
		  $(NULL)
INCS = $(addprefix -I, $(INCDIR))

TESTDIR	= ./tests
VECTOR_SRCS = $(shell find $(TESTDIR) -name '*.cpp' | grep -v 'gtest')

OBJDIR_FT	= ./objs_ft
OBJDIR_STL	= ./objs_stl
VECTOR_OBJS_FT = $(addprefix $(OBJDIR_FT)/, $(notdir $(VECTOR_SRCS:.cpp=.o)))
VECTOR_OBJS_STL = $(addprefix $(OBJDIR_STL)/, $(notdir $(VECTOR_SRCS:.cpp=.o)))

DEPS_FT = $(VECTOR_OBJS_FT:.o=.d)
DEPS_STL = $(VECTOR_OBJS_STL:.o=.d)

.PHONY: all
all: $(NAME_FT) $(NAME_STL)

-include $(DEPS_FT) $(DEPS_STL)

$(NAME_FT): $(OBJDIR_FT) $(VECTOR_OBJS_FT)
	$(CXX) $(CXXFLAGS) $(VECTOR_OBJS_FT) -o $@

$(NAME_STL): $(OBJDIR_STL) $(VECTOR_OBJS_STL)
	$(CXX) $(CXXFLAGS) -D USE_STL=1 $(VECTOR_OBJS_STL) -o $@

$(OBJDIR_FT):
	mkdir -p $@

$(OBJDIR_STL):
	mkdir -p $@

$(OBJDIR_FT)/%.o : $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR_STL)/%.o : $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -D USE_STL=1 -MMD -MP -c $< -o $@

.PHONY: run
run: $(NAME_FT) $(NAME_STL)
	./grademe.sh $(NAME_FT) $(NAME_STL)


.PHONY: ft
ft: $(NAME_FT)
	./$(NAME_FT)

.PHONY: stl
stl: $(NAME_STL)
	./$(NAME_STL)

.PHONY: sketch
sketch:
	$(CXX) sketch/main.cpp
	./a.out

.PHONY: clean
clean:
	$(RM) $(VECTOR_OBJS_FT) $(VECTOR_OBJS_STL) $(DEPS_FT) $(DEPS_STL)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME_FT) $(NAME_STL)
	$(RM) a.out ft_log stl_log

.PHONY: re
re: fclean all
