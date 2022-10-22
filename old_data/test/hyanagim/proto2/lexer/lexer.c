/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/28 19:43:31 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../main/minishell.h"

static int	match_quote(char *str, size_t *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	if (str[*i] != c)
		print_error("syntax error\n");
	return (1);
}

void	check_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			match_quote(line, &i, '"');
		if (line[i] == '\'')
			match_quote(line, &i, '\'');
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

void	change_cnt_quote(t_array *data, char c)
{
	if (c == '"')
		data->dquote++;
	if (c == '\'')
		data->squote++;
}

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c);

int	seq_quote(t_array *data, size_t *i, size_t *str_len, char c)
{
	int	cnt;

	cnt = 0;
	change_cnt_quote(data, c);
	(*i)++;
	if (data->line[*i] == '\0' || data->line[*i] == ' ')
		return (0);
	while (data->line[*i] != '\0' && data->line[*i] != '"'
		&& data->line[*i] != '\'' && data->line[*i] != ' ')
		(*i)++;
	if (data->line[*i] == '"')
		plus_pos(data, i, str_len, '"');
	if (data->line[*i] == '\'')
		plus_pos(data, i, str_len, '\'');
	return (1);
}

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c)
{
	(*i)++;
	change_cnt_quote(data, c);
	if (data->line[*i] == c)
		return (seq_quote(data, i, str_len, c));
	while (data->line[*i] != '\0' && data->line[*i] != c)
		(*i)++;
	while (data->line[*i] != '\0' && data->line[*i] != ' ')
	{
		change_cnt_quote(data, data->line[*i]);
		(*i)++;
	}
	if (data->dquote % 2 == 1)
		return (find_quote(data, i, '"'));
	if (data->squote % 2 == 1)
		return (find_quote(data, i, '\''));
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
	if (*str_len == 0)
		data->size += plus_pos(data, i, str_len, c);
	else
		plus_next_quote(data->line, i, str_len, c);
}

static void	count_size(t_array *data, char c)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == '"')
			plus_i(data, &i, &str_len, '"');
		if (data->line[i] == '\'')
			plus_i(data, &i, &str_len, '\'');
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
		if (data->line[i] == '"' && str_len == 0)
			push_q_element(data, &i, &str_len, '"');
		if (data->line[i] == '\'' && str_len == 0)
			push_q_element(data, &i, &str_len, '\'');
		if (data->line[i] == '"')
			plus_next_quote(data->line, &i, &str_len, '"');
		if (data->line[i] == '\'')
			plus_next_quote(data->line, &i, &str_len, '\'');
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
		if (str[i] == '"')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != '"')
				i++;
			if (str[i] == '\0')
				break ;
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		if (str[i] == '\'')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != '\'')
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

t_array	*lexer(t_array	*data)
{
	char	**temp;
	size_t	size;

	check_line(data->line);
	data->pos = 0;
	data->dquote = 0;
	data->squote = 0;
	data->size = 0;
	count_size(data, ' ');
	data->array = malloc(sizeof(char *) * (data->size + 1));
	if (data->array == NULL)
		return (NULL);
	data->array[data->size] = NULL;
	data->dquote = 0;
	data->squote = 0;
	split_line(data, ' ');
	shape_array(data);
	return (data);
}
