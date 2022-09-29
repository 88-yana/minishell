/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/29 17:00:21 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../../../trial/main/main.h"

#define DUBLEQ '"'
#define SINGLEQ '\''
#define DQ 0
#define SQ 1

static int	match_quote(char *str, size_t *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	if (str[*i] != c)
		; //printerror
	return (1);
}

void	check_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == DUBLEQ)
			match_quote(line, &i, DUBLEQ);
		if (line[i] == SINGLEQ)
			match_quote(line, &i, SINGLEQ);
		i++;
	}
	return ;
}

int	find_quote(t_array *data, size_t *i, char c)
{
	size_t	j;

	j = 0;
	while (data->line[(*i) + j] != '\0')
	{
		if (data->line[(*i) + j] == c)
		{
			(*i) += j + 1;
			return (1);
		}
		j++;
	}
	return (0);
}

// void	change_cnt_quote(t_array *data, char c)
// {
// 	if (c == DUBLEQ)
// 		data->quote[DQ]++;
// 	if (c == SINGLEQ)
// 		data->quote[SQ]++;
// }

int	bit(char c)
{
	if (c == DUBLEQ)
		return (DQ);
	if (c == SINGLEQ)
		return (SQ);
	return (2);
}

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c);

int	seq_quote(t_array *data, size_t *i, size_t *str_len, char c)
{
	int	cnt;

	cnt = 0;
	(data->quote[bit(c)])++;
	(*i)++;
	if (data->line[*i] == '\0' || data->line[*i] == ' ')
		return (0);
	while (data->line[*i] != '\0' && data->line[*i] != DUBLEQ
		&& data->line[*i] != SINGLEQ && data->line[*i] != ' ')
		(*i)++;
	if (data->line[*i] == DUBLEQ)
		plus_pos(data, i, str_len, DUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos(data, i, str_len, SINGLEQ);
	return (1);
}

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c)
{
	// while (data->line[*i] == c)
	// {
		(*i)++;
		(data->quote[bit(c)])++;
	// }
	if (*str_len == 0 && (data->line[*i] == '\0' || data->line[*i] == ' '))
		return (0);
	// if (data->line[*i] == c)
	// 	return (seq_quote(data, i, str_len, c));
	while (data->line[*i] != '\0' && data->line[*i] != c)
	{
		(*i)++;
		// (*str_len)++;
	}
	(*i)++;
	(data->quote[bit(c)])++;
	// (*str_len)++;
	while (data->line[*i] != '\0' && data->line[*i] != DUBLEQ
		&& data->line[*i] != SINGLEQ && data->line[*i] != ' ')
	{
		(*i)++;
		// (*str_len)++;
	}
	if (data->line[*i] == '\0')
		return (1);
	if (data->line[*i] == ' ')
		return (1);
	if (data->line[*i] == DUBLEQ)
		plus_pos(data, i, str_len, DUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos(data, i, str_len, SINGLEQ);
	// while (data->line[*i] != '\0' && data->line[*i] != ' ')
	// {
	// 	(data->quote[bit(c)])++;
	// 	(*i)++;
	// }
	// if (data->quote[DQ] % 2 == 1)
	// 	return (find_quote(data, i, DUBLEQ));
	// if (data->quote[SQ] % 2 == 1)
	// 	return (find_quote(data, i, SINGLEQ));
	return (1);
}

void	plus_next_quote(char *str, size_t *i, size_t *str_len, char c)
{
	(*i)++;
	(*str_len)++;
	while (str[*i] != '\0' && str[*i] != c)
	{
		(*i)++;
		(*str_len)++;
	}
	(*i)++;
	(*str_len)++;
}

void	plus_i(t_array *data, size_t *i, size_t *str_len, char c)
{
	// if (*str_len == 0)
	// 	data->size += plus_pos(data, i, str_len, c);
	// else
	// 	plus_next_quote(data->line, i, str_len, c);
	data->size += plus_pos(data, i, str_len, c);
}

static void	count_size(t_array *data, char c)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DUBLEQ)
			plus_i(data, &i, &str_len, DUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_i(data, &i, &str_len, SINGLEQ);
		if ((data->line[i] == c || data->line[i] == '\0') && str_len > 0)
			data->size++;
		if (data->line[i] == '\0')
			break ;
		if (data->line[i] != c)
			str_len++;
		else
			str_len = 0;
		i++;
	}
}

static void	free_array(t_array *data)
{
	size_t	i;

	i = 0;
	while (i < data->size)
	{
		free(data->array[i]);
		i++;
	}
	free(data->array);
	exit (1);
}

static void	push_element(t_array *data, size_t i, size_t str_len)
{
	data->array[data->pos] = malloc(str_len + 1);
	if (data->array[data->pos] == NULL)
		free_array(data);
	ft_strlcpy(data->array[data->pos], &(data->line[i - str_len]), str_len + 1);
	data->pos++;
}

static void	push_q_element(t_array *data, size_t *i, size_t *str_len, char c)
{
	size_t	start;

	start = *i;
	plus_pos(data, i, str_len, c);
	if (*i - start <= 2)
		return ;
	data->array[data->pos] = malloc(*i - start + 1);
	if (data->array[data->pos] == NULL)
		free_array(data);
	ft_strlcpy(data->array[data->pos], &(data->line[start]), *i - start + 1);
	data->pos++;
}

static void	split_line(t_array *data, char c)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DUBLEQ && str_len == 0)
			push_q_element(data, &i, &str_len, DUBLEQ);
		if (data->line[i] == SINGLEQ && str_len == 0)
			push_q_element(data, &i, &str_len, SINGLEQ);
		if (data->line[i] == DUBLEQ)
			plus_next_quote(data->line, &i, &str_len, DUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_next_quote(data->line, &i, &str_len, SINGLEQ);
		if ((data->line[i] == c || data->line[i] == '\0') && str_len > 0)
			push_element(data, i, str_len);
		if (data->line[i] == '\0')
			break ;
		if (data->line[i] != c)
			str_len++;
		else
			str_len = 0;
		i++;
	}
}

static void	delete_quote(char *str)
{
	size_t	i;

	if (ft_strchr(str, '$') != NULL)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DUBLEQ)
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != DUBLEQ)
				i++;
			if (str[i] == '\0')
				break ;
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		if (str[i] == SINGLEQ)
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != SINGLEQ)
				i++;
			if (str[i] == '\0')
				break ;
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		i++;
	}
}

static void	shape_array(t_array *data)
{
	size_t	i;

	i = 0;
	while (data->array[i] != NULL)
	{
		delete_quote(data->array[i]);
		i++;
	}
}

void	init(t_array *data)
{
	data->pos = 0;
	data->size = 0;
	data->quote[DQ] = 0;
	data->quote[SQ] = 0;
	data->length = NULL;
	data->array = NULL;
}

t_array	*lexer(t_array	*data)
{
	char	**temp;
	size_t	size;

	check_line(data->line);
	init(data);
	count_size(data, ' ');
	printf("%zu\n", data->size);
	data->quote[DQ] = 0;
	data->quote[SQ] = 0;
	data->array = malloc(sizeof(char *) * (data->size + 1));
	if (data->array == NULL)
		return (NULL);
	data->array[data->size] = NULL;
	split_line(data, ' ');
	// shape_array(data);
	return (data);
}
