/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:59:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 19:16:58 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDE_H
# define DIVIDE_H

# include "../../../../../libft/libft.h"
# include "../../../trial/main/main.h"
// # include "../../lexer/lexer.h"
// # include "structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool		check_line_div(char *line);
void		split_line_div(t_array *data, int type);
t_array		*malloc_element_div(t_array *data);
t_array		*malloc_array_div(t_array *data);
char		**lexer_div(t_array	*data);
bool		is_separator_div(char c);
size_t		arraylen(char **array);
char		**arrayjoin(char **arr1, char**arr2);
bool		is_sep(char c);
char		**delete_brank(char **array);
#endif