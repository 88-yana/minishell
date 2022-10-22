/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:51:33 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 16:41:49 by hyanagim         ###   ########.fr       */
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
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
t_list	*parser(char **array);

#endif