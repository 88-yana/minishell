/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/29 21:58:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"

void	go_advance(size_t *i, size_t *str_len)
{
	(*i)++;
	(*str_len)++;
}

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c)
{
	go_advance(i, str_len);
	while (data->line[*i] != c)
		go_advance(i, str_len);
	go_advance(i, str_len);
	while (data->line[*i] != '\0' && data->line[*i] != ' '
		&& data->line[*i] != SINGLEQ && data->line[*i] != DUBLEQ)
		go_advance(i, str_len);
	if (data->line[*i] == '\0' || data->line[*i] == ' ')
		return (1);
	if (data->line[*i] == DUBLEQ)
		plus_pos(data, i, str_len, DUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos(data, i, str_len, SINGLEQ);
	return (1);
}

static void	push_element(t_array *data, size_t i, size_t len, int type)
{
	if (type == 2)
		ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 1);
	data->pos++;
}

void	split_line(t_array *data, int type)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DUBLEQ)
			plus_pos(data, &i, &str_len, DUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_pos(data, &i, &str_len, SINGLEQ);
		if (type == 1)
			data->length[data->pos] = str_len + 1;
		if ((data->line[i] == ' ' || data->line[i] == '\0') && str_len > 0)
			push_element(data, i, str_len, type);
		if (data->line[i] == '\0')
			break ;
		if (data->line[i] != ' ')
			str_len++;
		else
			str_len = 0;
		i++;
	}
}

t_array	*lexer(t_array	*data)
{
	size_t	i;

	if (check_line(data->line) == false)
		return (NULL);
	if (malloc_array(data) == NULL)
		return (NULL);
	if (malloc_element(data) == NULL)
		return (NULL);
	data->pos = 0;
	split_line(data, 2);
	return (data);
}
