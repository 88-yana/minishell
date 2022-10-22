CC = cc
CFLAGS = #-fsanitize=address -g3
RLFLAGS = -I $(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline -lhistory
OPTIONS = -lreadline
SRCS_NAME = mandatory/main/main.c \
	mandatory/readline/readline.c \
	mandatory/envs/convert_envs.c \
	mandatory/envs/create.c \
	mandatory/envs/find_envs.c \
	mandatory/envs/envs_utils.c \
	mandatory/utils/substr_size_t.c \
	mandatory/utils/count_lstsize.c \
	mandatory/utils/safe_free_double.c \
	mandatory/builtin/builtin.c \
	mandatory/builtin/builtin_pwd.c \
	mandatory/builtin/builtin_cd.c \
	mandatory/builtin/builtin_echo.c \
	mandatory/builtin/builtin_env.c \
	mandatory/builtin/builtin_unset.c \
	mandatory/builtin/builtin_export.c \
	mandatory/builtin/builtin_exit.c \
	mandatory/parser/bool_pa.c \
	mandatory/parser/parser.c \
	mandatory/parser/check_arg.c \
	mandatory/lexer/bool.c \
	mandatory/lexer/check_quote.c \
	mandatory/lexer/delete_quote.c \
	mandatory/lexer/lexer.c \
	mandatory/lexer/malloc_free.c \
	mandatory/lexer/divide_one/bool_div.c \
	mandatory/lexer/divide_one/delete_brank.c \
	mandatory/lexer/divide_one/divide_redirect.c \
	mandatory/lexer/divide_one/lexer_div.c \
	mandatory/lexer/divide_one/malloc_free_div.c \
	mandatory/lexer/divide_double/arraylen.c \
	mandatory/lexer/divide_double/bool_re.c \
	mandatory/lexer/divide_double/divide_redirect.c \
	mandatory/lexer/divide_double/lexer_re.c \
	mandatory/lexer/divide_double/malloc_free_re.c \
	mandatory/lexer/divide_double/push_element.c \
	mandatory/execution/execution.c \
	mandatory/execution/find.c \
	mandatory/execution/pid.c \
	mandatory/execution/piped_commands.c \
	mandatory/execution/piped_commands_utils.c \
	mandatory/execution/heredoc.c \
	mandatory/redirection/redirection.c

# mandatory/main/main.c \
# mandatory/readline/readline.c \
# mandatory/builtin/builtin.c \
# mandatory/builtin/builtin_pwd.c \
# mandatory/builtin/builtin_cd.c \
# mandatory/builtin/builtin_echo.c \
# mandatory/builtin/builtin_env.c \
# mandatory/builtin/builtin_unset.c \
# mandatory/builtin/builtin_export.c \
# mandatory/builtin/builtin_exit.c \
# mandatory/envs/convert_types.c \
# mandatory/envs/envs_utils.c \
# mandatory/utils/count_lstsize.c \
# mandatory/utils/strjoin_delimiter.c \
# mandatory/utils/substr_size_t.c
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
