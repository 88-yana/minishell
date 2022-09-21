CC = cc
# CFLAGS = -Wall -Wextra -Werror

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

SRCS_DIR = ./main ./lexer
SRCS = $(addprefix , ${SRCS_NAME})

SRCS_NAME = minishell.c \
	lexer.c \

NAME = minishell
LIBFTDIR = ../../../libft
LIBFT_A = $(LIBFTDIR)/libft.a


all: $(NAME)

$(NAME):
	cc lexer/lexer.c main/minishell.c libft.a -lreadline
$(LIBFT_A):
	$(MAKE) -C $(LIBFTDIR)
$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR)
${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	mkdir -p ${OBJS_DIR}
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) -rf $(OBJS_DIR)
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFTDIR)
fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re
