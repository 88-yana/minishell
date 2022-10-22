#ifndef LEXER_TWO_SYMBOLS
# define LEXER_TWO_SYMBOLS

# include	"define.h"
# include	"../libft/libft.h"
# include	"lexer_one_symbol.h"
# include	"utils.h"

bool	check_line_re(char *line);
void	split_line_re(t_array *data, int type);
t_array	*malloc_element_re(t_array *data);
t_array	*malloc_array_re(t_array *data);
char	**lexer_re(t_array	*data);
bool	is_separator_re(char c, char d);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
void	free_array(t_array *data);
bool	is_null(char c);
bool	push_element_quo(t_array *data, size_t i, size_t len, int type);
bool	push_element_re(t_array *data, size_t *i, size_t *len, int type);
char	**divide_redirect(char **array);

#endif
