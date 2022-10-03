/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:51:33 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/03 10:21:31 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../../libft/libft.h"
# include "../../trial/main/main.h"
// # include "structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool	check_line(char *line);
void	split_line(t_array *data, int type);
t_array	*malloc_element(t_array *data);
t_array	*malloc_array(t_array *data);
t_array	*lexer(t_array	*data);
bool	is_separator(char c);
bool	check_arguments(char *str);
size_t	arraylen(char **array);
#endif