CC = cc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -lreadline
SRCS_NAME = mandatory/main/minishell.c \
	mandatory/parser/parser.c \
	mandatory/parser/parser_utils.c
SRCDIR = srcs
OBJDIR = objs
SRCS = $(addprefix $(SRCDIR)/, $(SRCS_NAME))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = minishell

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(shell find $(SRCDIR) -type d | sed 's/^$(SRCDIR)/$(OBJDIR)/g')

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTIONS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
