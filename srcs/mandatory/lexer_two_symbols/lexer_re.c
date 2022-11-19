/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_re.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/19 20:52:48 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_two_symbols.h"

static void	plus_pos_re(t_array *data, size_t *i, size_t *str_len, char c)
{
	go_advance(i, str_len);
	while (data->line[*i] != c)
		go_advance(i, str_len);
	go_advance(i, str_len);
	while (!is_separator_re(data->line[*i], data->line[*i + 1])
		&& !is_null(data->line[*i])
		&& data->line[*i] != SINGLEQ && data->line[*i] != DOUBLEQ)
		go_advance(i, str_len);
	if (is_null(data->line[*i])
		|| is_separator_re(data->line[*i], data->line[*i + 1]))
		return ;
	if (data->line[*i] == DOUBLEQ)
		plus_pos_re(data, i, str_len, DOUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos_re(data, i, str_len, SINGLEQ);
	return ;
}

void	split_line_re(t_array *data, int type)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DOUBLEQ)
			plus_pos_re(data, &i, &str_len, DOUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_pos_re(data, &i, &str_len, SINGLEQ);
		if (type == 1)
			data->strs_len[data->pos] = str_len + 1;
		if (push_element_quo(data, i, str_len, type))
			return ;
		if (push_element_re(data, &i, &str_len, type))
			return ;
		i++;
	}
}

char	**lexer_re(t_array	*data)
{
	if (malloc_array_re(data) == NULL)
		return (NULL);
	if (malloc_element_re(data) == NULL)
		return (NULL);
	data->pos = 0;
	split_line_re(data, 2);
	free(data->strs_len);
	return (data->array);
}
