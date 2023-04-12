NAME	:= n-puzzle
CFLAGS	:= -Wall -Wextra
# CFLAGS	+= -Werror
CFLAGS	:= -Ofast

HEADERS	:= -I ./include
SRCDIR	:= ./src
OBJDIR	:= ./obj
SRCS	:= $(shell find $(SRCDIR) -type f -name "*.cpp")
OBJS	:= $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiled: $(notdir $@)"

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(HEADERS) -o $(NAME) && echo "Linked: $(NAME)"

clean:
	rm -rf $(OBJDIR) && echo "Removed: $(OBJDIR)"

fclean: clean
	rm -f $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all, clean, fclean, re
.SILENT:
