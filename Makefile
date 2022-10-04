CC = cc
CFLAGS =
RLFLAGS = -I $(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline -lhistory
OPTIONS = -lreadline
SRCS_NAME = mandatory/main/main.c \
	mandatory/readline/readline.c \
	mandatory/builtin/builtin.c \
	mandatory/builtin/builtin_pwd.c \
	mandatory/builtin/builtin_cd.c \
	mandatory/builtin/builtin_echo.c \
	mandatory/builtin/builtin_env.c \
	mandatory/builtin/builtin_export.c \
	mandatory/builtin/builtin_exit.c \
	mandatory/envs/convert_types.c \
	mandatory/envs/envs_utils.c \
	mandatory/utils/count_lstsize.c \
	mandatory/utils/strjoin_delimiter.c \
	mandatory/utils/substr_size_t.c
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
