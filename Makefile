NAME	:= n-puzzle
CC		:= g++
CFLAGS	:= -Wall -Wextra -Ofast
# CFLAGS	+= -Werror

HEADERS	:= -I ./include
SRCDIR	:= ./src
OBJDIR	:= ./obj
SRCS	:= $(shell cd $(SRCDIR) && find . -name "*.cpp")
OBJS	:= $(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiled: $(notdir $@)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(HEADERS) -o $(NAME) && echo "Linked: $(NAME)"

clean:
	rm -rf $(OBJDIR) && echo "Removed: $(OBJDIR)"

fclean: clean
	rm -f $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all, clean, fclean, re
.SILENT:
