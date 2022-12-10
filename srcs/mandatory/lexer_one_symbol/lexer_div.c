/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_div.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/21 01:37:17 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_one_symbol.h"

static void	plus_pos_div(t_array *data, size_t *i, size_t *str_len, char c)
{
	go_advance(i, str_len);
	while (data->line[*i] != c)
		go_advance(i, str_len);
	go_advance(i, str_len);
	while (!is_separator_div(data->line[*i])
		&& data->line[*i] != SINGLEQ && data->line[*i] != DOUBLEQ)
		go_advance(i, str_len);
	if (is_separator_div(data->line[*i]))
		return ;
	if (data->line[*i] == DOUBLEQ)
		plus_pos_div(data, i, str_len, DOUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos_div(data, i, str_len, SINGLEQ);
	return ;
}

static void	copy_to_array(t_array *data, size_t i, size_t len)
{
	if (data->line[i] == '\0')
		ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 1);
	else if (i == 0)
		ft_strlcpy(data->array[data->pos], &(data->line[i]), 2);
	else
	{
		ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 1);
		ft_strlcpy(data->array[data->pos + 1], &(data->line[i]), 2);
	}
}

static void	push_element_div(t_array *data, size_t i, size_t len, int type)
{
	if (data->line[i] == '\0' && is_separator_div(data->line[i - 1]))
		return ;
	if (ft_strcmp(data->line, "<<") == 0 || ft_strcmp(data->line, ">>") == 0
		|| ft_strcmp(data->line, "&&") == 0 || ft_strcmp(data->line, "||") == 0)
	{
		if (type == 2 && data->pos == 0)
			ft_strlcpy(data->array[data->pos], data->line, 3);
		data->pos = 1;
		return ;
	}
	if (type == 2)
		copy_to_array(data, i, len);
	if (data->line[i] == '\0')
	{
		if (type == 1)
			data->strs_len[data->pos] = len + 1;
		data->pos++;
	}
	else if (i == 0)
	{
		if (type == 1)
			data->strs_len[data->pos] = len + 1;
		data->pos++;
	}
	else
	{
		if (type == 1)
			data->strs_len[data->pos] = len + 1;
		if (type == 1)
			data->strs_len[data->pos + 1] = len + 1;
		data->pos += 2;
	}
}

void	split_line_div(t_array *data, int type)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DOUBLEQ)
			plus_pos_div(data, &i, &str_len, DOUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_pos_div(data, &i, &str_len, SINGLEQ);
		if (type == 1)
			data->strs_len[data->pos] = str_len + 1;
		if (is_separator_div(data->line[i]))
		{
			push_element_div(data, i, str_len, type);
			str_len = 0;
		}
		else
			str_len++;
		if (data->line[i] == '\0')
			break ;
		i++;
	}
}

char	**lexer_div(t_array	*data)
{
	if (malloc_array_div(data) == NULL)
		return (NULL);
	if (malloc_element_div(data) == NULL)
		return (NULL);
	data->pos = 0;
	split_line_div(data, 2);
	free(data->strs_len);
	return (data->array);
}
