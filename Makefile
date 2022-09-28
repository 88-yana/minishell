CC = cc
CFLAGS =
RLFLAGS = -I $(shell brew --prefix readline)/include -lreadline -lhistory -L$(shell brew --prefix readline)/lib
OPTIONS = -lreadline
SRCS_NAME = mandatory/main/main.c \
	mandatory/readline/readline.c
SRCDIR = srcs
OBJDIR = objs
SRCS = $(addprefix $(SRCDIR)/, $(SRCS_NAME))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = minishell

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(shell find $(SRCDIR) -type d | sed 's/^$(SRCDIR)/$(OBJDIR)/g')

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(RLFLAGS) $(OPTIONS) $(OBJS) libft/libft.a -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(RLFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)
	$(MAKE) fclean -C ./libft

fclean: clean
	$(RM) $(NAME)

re: fclean all
