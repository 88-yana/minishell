#ifndef DEBUG_H
# define DEBUG_H

# include	"define.h"
# include	"../libft/libft.h"

t_order	*make_command(t_type type, char **cmd, char *file, t_list *shell);
size_t	test(t_list **list);
void	display_command(t_list *command_line);
void	display_array(char ** arr);

#endif