/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_quote.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:59:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/03 17:14:34 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDE_QUOTE_H
# define DIVIDE_QUOTE_H

# include "../../../../libft/libft.h"
# include "../../../trial/main/main.h"
// # include "../../lexer/lexer.h"
// # include "structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool	check_line_re(char *line);
void	split_line_re(t_array *data, int type);
t_array	*malloc_element_re(t_array *data);
t_array	*malloc_array_re(t_array *data);
char	**lexer_re(t_array	*data);
bool	is_separator_re(char c, char d);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
#endif