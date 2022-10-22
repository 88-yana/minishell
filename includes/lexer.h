/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:35:53 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 19:44:53 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include	"define.h"
# include	"../libft/libft.h"
# include	"lexer_one_symbol.h"
# include	"lexer_two_symbols.h"
# include	"util.h"

bool	check_line(char *line);
void	split_line(t_array *data, int type);
t_array	*malloc_element(t_array *data);
t_array	*malloc_array(t_array *data);
bool	is_separator(char c);
void	plus_pos(t_array *data, size_t *i, size_t *str_len, char c);
char	**lexer(char *line);
#endif
