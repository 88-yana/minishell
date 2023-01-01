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
	mandatory/execution/redirection_utils.c \
	mandatory/execution/asterisk.c \
	mandatory/execution/asterisk_check.c \
	mandatory/execution/asterisk_utils.c \
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

SRCS_NAME_BONUS = bonus/main/main.c \
	bonus/readline/readline.c \
	bonus/builtin/builtin_cd.c \
	bonus/builtin/builtin_echo.c \
	bonus/builtin/builtin_env.c \
	bonus/builtin/builtin_exit.c \
	bonus/builtin/builtin_export.c \
	bonus/builtin/builtin_pwd.c \
	bonus/builtin/builtin_unset.c \
	bonus/builtin/builtin.c \
	bonus/utils/count_lstsize.c \
	bonus/utils/safe_free_double.c \
	bonus/utils/strjoin_delimiter.c \
	bonus/utils/substr_size_t.c \
	bonus/utils/arraylen.c \
	bonus/envs/convert_envs.c \
	bonus/envs/create.c \
	bonus/envs/envs_utils.c \
	bonus/envs/find_envs.c \
	bonus/envs/lexer_envs.c \
	bonus/execution/execution.c \
	bonus/execution/find.c \
	bonus/execution/heredoc.c \
	bonus/execution/pid.c \
	bonus/execution/piped_commands.c \
	bonus/execution/piped_commands_utils.c \
	bonus/execution/redirection.c \
	bonus/execution/redirection_utils.c \
	bonus/execution/asterisk.c \
	bonus/execution/asterisk_check.c \
	bonus/execution/asterisk_utils.c \
	bonus/execution/delete_quote.c \
	bonus/reader/bool.c \
	bonus/reader/cutline.c \
	bonus/reader/list_to_subshell.c \
	bonus/reader/list.c \
	bonus/reader/make_cmd.c \
	bonus/reader/reader.c \
	bonus/reader/slist.c \
	bonus/reader/sort.c \
	bonus/reader/str_to_aim.c \
	bonus/reader/str_to_cmd.c \
	bonus/reader/str_to_list.c \
	bonus/reader/match.c \
	bonus/reader/check_quote.c \
	bonus/reader/make_command.c

SRCDIR = srcs
OBJDIR = objs
SRCS = $(addprefix $(SRCDIR)/, $(SRCS_NAME))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = minishell
NAME_BONUS = minishell_bonus

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

duplicate:
	echo $(shell find $(SRCDIR) -type d)

test:$(NAME)
	bash test.sh

clean:
	rm -rf $(OBJDIR)
	$(MAKE) fclean -C ./libft

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re