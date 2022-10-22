/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:51:33 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/19 13:01:14 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../../libft/libft.h"
# include "../../../include/minishell.h"
# include "../../../include/structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool	is_delimiter(char *str);
bool	check_line(char *line);
bool	is_separator(char c);
bool	check_arguments(char *str);
bool	is_bra(char *str);
bool	is_pipe(char *str);
bool	is_redirection(char *str);
void	split_line(t_array *data, int type);
t_array	*malloc_element(t_array *data);
t_array	*malloc_array(t_array *data);
t_array	*lexer(t_array	*data);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
t_list	*to_parser(char **array);

#endif