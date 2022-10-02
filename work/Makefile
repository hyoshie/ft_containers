NAME_FT = $(BINDIR)/output_ft
NAME_STL = $(BINDIR)/output_stl

BENCHMARK_FT = $(BINDIR)/benchmark_ft
BENCHMARK_STL = $(BINDIR)/benchmark_stl

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

BINDIR  = ./bin
LOGDIR  = ./log

INCDIR = ./include \
		  $(NULL)
INCS = $(addprefix -I, $(INCDIR))

OBJDIR_FT	= ./objs_ft
OBJDIR_STL	= ./objs_stl

OUTPUT_DIR	= ./test/output
OUTPUT_SRCS = $(shell find $(OUTPUT_DIR) -name '*.cpp')

OUTPUT_OBJS_FT = $(addprefix $(OBJDIR_FT)/, $(notdir $(OUTPUT_SRCS:.cpp=.o)))
OUTPUT_OBJS_STL = $(addprefix $(OBJDIR_STL)/, $(notdir $(OUTPUT_SRCS:.cpp=.o)))

OUTPUT_DEPS_FT = $(OUTPUT_OBJS_FT:.o=.d)
OUTPUT_DEPS_STL = $(OUTPUT_OBJS_STL:.o=.d)

BENCHMARK_DIR	= ./test/benchmark
BENCHMARK_SRCS = $(shell find $(BENCHMARK_DIR) -name '*.cpp')

BENCHMARK_OBJS_FT = $(addprefix $(OBJDIR_FT)/, $(notdir $(BENCHMARK_SRCS:.cpp=.o)))
BENCHMARK_OBJS_STL = $(addprefix $(OBJDIR_STL)/, $(notdir $(BENCHMARK_SRCS:.cpp=.o)))

BENCHMARK_DEPS_FT = $(BENCHMARK_OBJS_FT:.o=.d)
BENCHMARK_DEPS_STL = $(BENCHMARK_OBJS_STL:.o=.d)

.PHONY: all
all: $(NAME_FT) $(NAME_STL)

-include $(OUTPUT_DEPS_FT) $(OUTPUT_DEPS_STL) $(BENCHMARK_DEPS_FT) $(BENCHMARK_DEPS_STL)

$(NAME_FT): $(OBJDIR_FT) $(OUTPUT_OBJS_FT)
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(OUTPUT_OBJS_FT) -o $@

$(NAME_STL): $(OBJDIR_STL) $(OUTPUT_OBJS_STL)
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -D USE_STL=1 $(OUTPUT_OBJS_STL) -o $@

$(BENCHMARK_FT): $(OBJDIR_FT) $(BENCHMARK_OBJS_FT)
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(BENCHMARK_OBJS_FT) -o $@

$(BENCHMARK_STL): $(OBJDIR_STL) $(BENCHMARK_OBJS_STL)
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -D USE_STL=1 $(BENCHMARK_OBJS_STL) -o $@

$(BINDIR):
	mkdir -p $@

$(LOGDIR):
	mkdir -p $@

$(OBJDIR_FT):
	mkdir -p $@

$(OBJDIR_STL):
	mkdir -p $@

$(OBJDIR_FT)/%.o : $(OUTPUT_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR_STL)/%.o : $(OUTPUT_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -D USE_STL=1 -MMD -MP -c $< -o $@

$(OBJDIR_FT)/%.o : $(BENCHMARK_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR_STL)/%.o : $(BENCHMARK_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -D USE_STL=1 -MMD -MP -c $< -o $@

.PHONY: run
run: $(NAME_FT) $(NAME_STL) $(LOGDIR)
	./eval_output.sh $(NAME_FT) $(NAME_STL)

.PHONY: bench
bench: $(BENCHMARK_FT) $(BENCHMARK_STL) $(LOGDIR)
	./eval_benchmark.sh $(BENCHMARK_FT) $(BENCHMARK_STL)

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
	$(RM) $(OUTPUT_OBJS_FT) $(OUTPUT_OBJS_STL) $(OUTPUT_DEPS_FT) $(OUTPUT_DEPS_STL)
	$(RM) $(BENCHMARK_OBJS_FT) $(BENCHMARK_OBJS_STL) $(BENCHMARK_DEPS_FT) $(BENCHMARK_DEPS_STL)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME_FT) $(NAME_STL) $(BENCHMARK_FT) $(BENCHMARK_STL)
	$(RM) a.out ft_log stl_log googletest

.PHONY: re
re: fclean all
