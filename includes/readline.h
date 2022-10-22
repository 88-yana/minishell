#ifndef READLINE_H
# define READLINE_H

# include	<stdio.h>
# include	<signal.h>
# include	<stdbool.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../libft/libft.h"
# include	"define.h"

# define PROMPT "minishell$ "

char	*read_line_from_prompt(void);

#endif
