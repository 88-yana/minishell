CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ./includes/mandatory/ -I ./includes/bonus/
RLFLAGS = -I $(shell brew --prefix readline)/include -L$(shell brew --prefix readline)/lib -lreadline -lhistory
SRCS_NAME_MANDATORY = mandatory/main/main.c \
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
	mandatory/execution/heredoc_unlink.c \
	mandatory/execution/pid.c \
	mandatory/execution/piped_commands.c \
	mandatory/execution/piped_commands_utils.c \
	mandatory/execution/redirection.c \
	mandatory/execution/redirection_utils.c \
	mandatory/execution/asterisk.c \
	mandatory/execution/asterisk_check.c \
	mandatory/execution/asterisk_utils.c \
	mandatory/execution/delete_quote.c \
	mandatory/execution/signal.c \
	mandatory/reader/bool.c \
	mandatory/reader/check_lex.c \
	mandatory/reader/check_quote.c \
	mandatory/reader/cutline.c \
	mandatory/reader/free.c \
	mandatory/reader/list_to_subshell.c \
	mandatory/reader/list.c \
	mandatory/reader/make_cmd.c \
	mandatory/reader/make_command.c \
	mandatory/reader/match.c \
	mandatory/reader/reader.c \
	mandatory/reader/slist.c \
	mandatory/reader/sort.c \
	mandatory/reader/sort_red_str.c \
	mandatory/reader/str_to_aim.c \
	mandatory/reader/str_to_cmd.c \
	mandatory/reader/str_to_list.c

SRCS_NAME_BONUS = bonus/main/main_bonus.c \
	bonus/readline/readline_bonus.c \
	bonus/builtin/builtin_cd_bonus.c \
	bonus/builtin/builtin_echo_bonus.c \
	bonus/builtin/builtin_env_bonus.c \
	bonus/builtin/builtin_exit_bonus.c \
	bonus/builtin/builtin_export_bonus.c \
	bonus/builtin/builtin_pwd_bonus.c \
	bonus/builtin/builtin_unset_bonus.c \
	bonus/builtin/builtin_bonus.c \
	bonus/utils/count_lstsize_bonus.c \
	bonus/utils/safe_free_double_bonus.c \
	bonus/utils/strjoin_delimiter_bonus.c \
	bonus/utils/substr_size_t_bonus.c \
	bonus/utils/arraylen_bonus.c \
	bonus/envs/convert_envs_bonus.c \
	bonus/envs/create_bonus.c \
	bonus/envs/envs_utils_bonus.c \
	bonus/envs/find_envs_bonus.c \
	bonus/envs/lexer_envs_bonus.c \
	bonus/execution/execution_bonus.c \
	bonus/execution/find_bonus.c \
	bonus/execution/heredoc_bonus.c \
	bonus/execution/heredoc_unlink_bonus.c \
	bonus/execution/pid_bonus.c \
	bonus/execution/piped_commands_bonus.c \
	bonus/execution/piped_commands_utils_bonus.c \
	bonus/execution/redirection_bonus.c \
	bonus/execution/redirection_utils_bonus.c \
	bonus/execution/asterisk_bonus.c \
	bonus/execution/asterisk_check_bonus.c \
	bonus/execution/asterisk_utils_bonus.c \
	bonus/execution/delete_quote_bonus.c \
	bonus/execution/signal_bonus.c \
	bonus/reader/bool_bonus.c \
	bonus/reader/cutline_bonus.c \
	bonus/reader/check_lex_bonus.c \
	bonus/reader/list_to_subshell_bonus.c \
	bonus/reader/list_bonus.c \
	bonus/reader/make_cmd_bonus.c \
	bonus/reader/reader_bonus.c \
	bonus/reader/slist_bonus.c \
	bonus/reader/sort_bonus.c \
	bonus/reader/sort_red_str_bonus.c \
	bonus/reader/str_to_aim_bonus.c \
	bonus/reader/str_to_cmd_bonus.c \
	bonus/reader/str_to_list_bonus.c \
	bonus/reader/match_bonus.c \
	bonus/reader/check_quote_bonus.c \
	bonus/reader/free_bonus.c \
	bonus/reader/make_command_bonus.c

SRCDIR = srcs
OBJDIR = objs
SRCS_MANDATORY = $(addprefix $(SRCDIR)/, $(SRCS_NAME_MANDATORY))
SRCS_BONUS = $(addprefix $(SRCDIR)/, $(SRCS_NAME_BONUS))
OBJS_MANDATORY = $(SRCS_MANDATORY:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = minishell

ifdef BONUS
	OBJS = $(OBJS_BONUS)
else
	OBJS = $(OBJS_MANDATORY)
endif

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(shell find $(SRCDIR) -type d | sed 's/^$(SRCDIR)/$(OBJDIR)/g')

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(RLFLAGS) $(INCLUDES) $(OBJS) libft/libft.a -o $(NAME)

$(OBJDIR)/mandatory/readline/readline.o: $(SRCDIR)/mandatory/readline/readline.c
	$(CC) $(CFLAGS) $(INCLUDES) -I $(shell brew --prefix readline)/include -o $@ -c $<

$(OBJDIR)/bonus/readline/readline_bonus.o: $(SRCDIR)/bonus/readline/readline_bonus.c
	$(CC) $(CFLAGS) $(INCLUDES) -I $(shell brew --prefix readline)/include -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)
	$(MAKE) fclean -C ./libft

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	make BONUS=1 all

.PHONY: all clean fclean re bonus
