/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:59:21 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/03 14:00:08 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
void	go_advance(size_t *i, size_t *str_len);
#endif