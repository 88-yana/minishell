/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/29 19:22:21 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../../libft/libft.h"
#include "main.h"
// #include "../../../../../minishell/include/minishell.h"

#define DUBLEQ '"'
#define SINGLEQ '\''

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

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c)
{
	(*i)++;
	(*str_len)++;
	while (data->line[*i] != c)
	{
		(*i)++;
		(*str_len)++;
	}
	(*i)++;
	(*str_len)++;
	while (data->line[*i] != '\0' && data->line[*i] != DUBLEQ
		&& data->line[*i] != SINGLEQ && data->line[*i] != ' ')
	{
		(*i)++;
		(*str_len)++;
	}
	if (data->line[*i] == '\0')
		return (1);
	if (data->line[*i] == ' ')
		return (1);
	if (data->line[*i] == DUBLEQ)
		plus_pos(data, i, str_len, DUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos(data, i, str_len, SINGLEQ);
	return (1);
}

static void	count_size(t_array *data)
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
		if ((data->line[i] == ' ' || data->line[i] == '\0') && str_len > 0)
			data->size++;
		if (data->line[i] == '\0')
			break ;
		if (data->line[i] != ' ')
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

static void	split_line(t_array *data)
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
		if ((data->line[i] == ' ' || data->line[i] == '\0') && str_len > 0)
			push_element(data, i, str_len);
		if (data->line[i] == '\0')
			break ;
		if (data->line[i] != ' ')
			str_len++;
		else
			str_len = 0;
		i++;
	}
}

void	init(t_array *data)
{
	data->pos = 0;
	data->size = 0;
	data->length = NULL;
	data->array = NULL;
}

t_array	*lexer(t_array	*data)
{
	char	**temp;
	size_t	size;

	check_line(data->line);
	init(data);
	count_size(data);
	printf("size is %zu\n", data->size);
	data->array = malloc(sizeof(char *) * (data->size + 1));
	if (data->array == NULL)
		return (NULL);
	data->array[data->size] = NULL;
	split_line(data);
	// shape_array(data);
	return (data);
}
