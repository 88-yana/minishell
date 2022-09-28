CC = cc
CFLAGS = -Wall -Wextra
RLFLAGS = -I $(shell brew --prefix readline)/include -lreadline -lhistory -L$(shell brew --prefix readline)/lib
SRCS = $(shell find . -type f -mindepth 2 -name *.c)
OBJS = $(SRCS:%.c=%.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ../../libft
	$(CC) $(CFLAGS) $(RLFLAGS) $(OBJS) ../../libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(RLFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all