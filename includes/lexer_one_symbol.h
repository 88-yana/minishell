#ifndef LEXER_ONE_SYMBOL
# define LEXER_ONE_SYMBOL

# include	"define.h"
# include	"../libft/libft.h"
# include	"utils.h"

bool	check_line_div(char *line);
void	split_line_div(t_array *data, int type);
t_array	*malloc_element_div(t_array *data);
t_array	*malloc_array_div(t_array *data);
char	**lexer_div(t_array	*data);
bool	is_separator_div(char c);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
bool	is_sep(char c);
char	**delete_brank(char **array);

#endif
