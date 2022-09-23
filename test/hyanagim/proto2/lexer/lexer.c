/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/23 20:11:03 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../main/minishell.h"

static int	match_quote(char *str, size_t *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
	{
		printf("%c", str[*i]);
		(*i)++;
	}
	if (str[*i] != c)
		print_error("syntax error\n");
	return (1);
}

typedef struct s_split
{
	char	*line;
	size_t	pos;
	size_t	size;
	size_t	dquote;
	size_t	squote;
	char	**array;
}	t_array;

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

// typedef struct s_check
// {
// 	int		ok_line;
// 	int		ok_hairetu;
// 	char	**temp;
// }	t_check;

static int	plus_pos(t_array *data, size_t *i, size_t *str_len, char c)
{
	(*i)++;
	if (c == '"')
		data->dquote++;
	if (c == '\'')
		data->squote++;
	if (data->line[*i] == c)
	{
		if (c == '"')
			data->dquote++;
		if (c == '\'')
			data->squote++;
		(*i)++;
		if (data->line[*i] == '\0' || data->line[*i] == ' ')
			return (0);
		// while(data->line[*i] != '\0' && data->line[*i] != c)
		// {
		// 	(*i)++;
		// 	(*str_len)++;
		// }
		// return (1);
		while (data->line[*i] != '\0' && data->line[*i] != '"' && data->line[*i] != '\'' && data->line[*i] != ' ')
			(*i)++;
		if (data->line[*i] == '"')
			plus_pos(data, i, str_len, '"');
		if (data->line[*i] == '\'')
			plus_pos(data, i, str_len, '\'');
		return (1);
	}
	while (data->line[*i] != '\0' && data->line[*i] != c)
	{
		(*i)++;
	}
	while (data->line[*i] != '\0' && data->line[*i] != ' ')
	{
		if (data->line[*i] == '"')
			data->dquote++;
		if (data->line[*i] == '\'')
			data->squote++;
		(*i)++;
	}
	if (data->dquote % 2 == 1)
	{
		size_t j = 0;
		while (data->line[(*i) + j] != '\0')
		{
			if (data->line[(*i) + j] == '"')
			{
				(*i) += j + 1;
				return (1);
			}
			j++;
		}
	}
	if (data->squote % 2 == 1)
	{
		size_t j = 0;
		while (data->line[(*i) + j] != '\0')
		{
			if (data->line[(*i) + j] == '\'')
			{
				(*i) += j + 1;
				return (1);
			}
			j++;
		}
	}
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

static size_t	count_size(t_array *data, char c)
{
	size_t	i;
	size_t	j;
	size_t	cnt;
	size_t	str_len;

	i = 0;
	cnt = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == '"' && str_len == 0)
			cnt += plus_pos(data, &i, &str_len, '"');
		if (data->line[i] == '\'' && str_len == 0)
			cnt += plus_pos(data, &i, &str_len, '\'');
		if (data->line[i] == '"')
			plus_next_quote(data->line, &i, &str_len, '"');
		if (data->line[i] == '\'')
			plus_next_quote(data->line, &i, &str_len, '\'');
		if ((data->line[i] == c || data->line[i] == '\0') && str_len > 0)
			cnt++;
		if (data->line[i] == '\0')
			break ;
		if (data->line[i] != c)
			str_len++;
		else
			str_len = 0;
		i++;
	}
	return (cnt);
}


static void	free_array(t_array *data)
{
	size_t	i;

	i = 0;
	while (i < data->pos)
	{
		free(data->array[i]);
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

static void	push_quote_element(t_array *data, size_t *i, size_t *str_len, char c)
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
			push_quote_element(data, &i, &str_len, '"');
		if (data->line[i] == '\''&& str_len == 0)
			push_quote_element(data, &i, &str_len, '\'');
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

char	**lexer(char *line)
{
	char	**temp;
	size_t	size;
	t_array data;

	check_line(line);
	data.line = line;
	data.pos = 0;
	data.dquote = 0;
	data.squote = 0;
	data.size = count_size(&data, ' ');
	data.array = malloc(sizeof(char *) * (data.size + 1));
	if (data.array == NULL)
		return (NULL);
	data.array[data.size] = NULL;
	data.pos = 0;
	data.dquote = 0;
	data.squote = 0;
	split_line(&data, ' ');
	int i = 0;
	printf("size is %zu\n", data.size);
	while(data.array[i] != NULL)
	{
		printf("data is 『%s』\n", data.array[i]);
		i++;
	}
	return (temp);
}
