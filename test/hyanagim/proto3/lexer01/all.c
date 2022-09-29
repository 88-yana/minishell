/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:34:44 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/28 20:49:15 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	match_quote(char *str, size_t *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	if (str[*i] != c)
		;  //printerror
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

int	main(void)
{
	
	return 0;
}