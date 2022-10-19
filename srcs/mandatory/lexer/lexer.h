/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:59:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/19 12:59:54 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../../libft/libft.h"
# include "../../../include/minishell.h"
# include "divide_one/divide.h"
# include "divide_double/divide_quote.h"
// # include "structure.h"

# define DUBLEQ '"'
# define SINGLEQ '\''

bool	check_line(char *line);
void	split_line(t_array *data, int type);
t_array	*malloc_element(t_array *data);
t_array	*malloc_array(t_array *data);
t_array	*lexer(t_array	*data);
bool	is_separator(char c);
void	go_advance(size_t *i, size_t *str_len);
void	plus_pos(t_array *data, size_t *i, size_t *str_len, char c);
#endif