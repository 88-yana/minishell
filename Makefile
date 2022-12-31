CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./includes/ #-fsanitize=address -g3
RLFLAGS = -I $(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline -lhistory
SRCS_NAME = mandatory/main/main.c \
	mandatory/readline/readline.c \
	mandatory/lexer/lexer.c \
	mandatory/lexer/check_quote.c \
	mandatory/lexer/malloc_free.c \
	mandatory/lexer/match.c \
	mandatory/lexer/bool.c \
	mandatory/lexer_one_symbol/bool_div.c \
	mandatory/lexer_one_symbol/lexer_div.c \
	mandatory/lexer_one_symbol/delete_brank.c \
	mandatory/lexer_one_symbol/malloc_free_div.c \
	mandatory/lexer_two_symbols/divide_redirect.c \
	mandatory/lexer_two_symbols/push_element.c \
	mandatory/lexer_two_symbols/bool_re.c \
	mandatory/lexer_two_symbols/lexer_re.c \
	mandatory/lexer_two_symbols/malloc_free_re.c \
	mandatory/parser/parser.c \
	mandatory/parser/check_arg.c \
	mandatory/parser/bool_pa.c \
	mandatory/parser/utils.c \
	mandatory/parser/command_line.c \
	mandatory/parser/delimiter.c \
	mandatory/parser/piped_line.c \
	mandatory/parser/pipe.c \
	mandatory/parser/arguments.c \
	mandatory/parser/redirection.c \
	mandatory/parser/subshell.c \
	mandatory/parser/talloc.c \
	mandatory/parser/test.c \
	mandatory/parser/sort.c \
	mandatory/parser/list.c \
	mandatory/parser/command.c \
	mandatory/parser/make_command.c \
	mandatory/parser/realloc.c \
	mandatory/builtin/builtin_cd.c \
	mandatory/builtin/builtin_echo.c \
	mandatory/builtin/builtin_env.c \
	mandatory/builtin/builtin_exit.c \
	mandatory/builtin/builtin_export.c \
	mandatory/builtin/builtin_pwd.c \
	mandatory/builtin/builtin_unset.c \
	mandatory/builtin/builtin.c \
	mandatory/utils/count_lstsize.c \
	mandatory/utils/safe_free_double.c \
	mandatory/utils/strjoin_delimiter.c \
	mandatory/utils/substr_size_t.c \
	mandatory/utils/go_advance.c \
	mandatory/utils/arraylen.c \
	mandatory/envs/convert_envs.c \
	mandatory/envs/create.c \
	mandatory/envs/envs_utils.c \
	mandatory/envs/find_envs.c \
	mandatory/envs/lexer_envs.c \
	mandatory/execution/execution.c \
	mandatory/execution/find.c \
	mandatory/execution/heredoc.c \
	mandatory/execution/pid.c \
	mandatory/execution/piped_commands.c \
	mandatory/execution/piped_commands_utils.c \
	mandatory/execution/redirection.c \
	mandatory/execution/asterisk.c \
	mandatory/execution/delete_quote.c

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
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) libft/libft.a -o $(NAME)

$(OBJDIR)/mandatory/readline/readline.o: $(SRCDIR)/mandatory/readline/readline.c
	$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

a:$(NAME)
	./minishell < line.txt
ans:$(NAME)
	./minishell < line.txt > ans.txt
b:$(NAME)
	./minishell < line.txt | diff - ans.txt
ok:
	./minishell < infile.txt > ok.txt

test:
	echo hello
	bash test.sh

lex:
	cc srcs/mandatory/lexer/*c srcs/mandatory/lexer_one_symbol/*c srcs/mandatory/lexer_two_symbols/*c srcs/mandatory/utils/*c libft/libft.a
	./a.out

par:
	gcc srcs/mandatory/parser/*c srcs/mandatory/utils/*c libft/libft.a
	./a.out

sub: $(NAME)
	./minishell < infile.txt

clean:
	rm -rf $(OBJDIR)
	$(MAKE) fclean -C ./libft

fclean: clean
	$(RM) $(NAME)

re: fclean all
