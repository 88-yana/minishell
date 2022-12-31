CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./includes/ #-fsanitize=address -g3
RLFLAGS = -I $(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline -lhistory
SRCS_NAME = mandatory/main/main.c \
	mandatory/readline/readline.c \
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
	mandatory/execution/delete_quote.c \
	mandatory/reader/bool.c \
	mandatory/reader/cutline.c \
	mandatory/reader/list_to_subshell.c \
	mandatory/reader/list.c \
	mandatory/reader/make_cmd.c \
	mandatory/reader/reader.c \
	mandatory/reader/slist.c \
	mandatory/reader/sort.c \
	mandatory/reader/str_to_aim.c \
	mandatory/reader/str_to_cmd.c \
	mandatory/reader/str_to_list.c \
	mandatory/reader/match.c \
	mandatory/reader/check_quote.c \
	mandatory/reader/make_command.c

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

.PHONY: test