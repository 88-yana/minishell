/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/23 16:06:36 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include "../main/minishell.h"

static int	match_quote(char *str, size_t *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	if (str[*i] == c)
		(*i)++;
	else
		print_error("syntax error\n");
	return (1);
}

void	check_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
			match_quote(line, &i, '\"');
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

static int	plus_pos(char *str, size_t *i, char c)
{
	(*i)++;
	if (str[*i] == c)
	{
		(*i)++;
		if (str[*i] == '\0' || str[*i] == c)
			return (0);
		while(str[*i] != '\0' && str[*i] != c)
			(*i)++;
		return (1);
	}
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	while (str[*i] != '\0' && str[*i] != ' ')
		(*i)++;
	return (1);
}

static size_t	count_size(char *str, char c)
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
		if (str[i] == '"')
			cnt += plus_pos(str, &i, '"');
		if (str[i] == '\'')
			cnt += plus_pos(str, &i, '\'');
		if ((str[i] == c || str[i] == '\0') && str_len > 0)
			cnt++;
		if (str[i] == '\0')
			break ;
		if (str[i] != c)
			str_len++;
		else
			str_len = 0;
		i++;
	}
	return (cnt);
}

typedef struct s_split
{
	char	*line;
	size_t	pos;
	size_t	size;
	char	**array;
}	t_array;

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

static void	push_quote_element(t_array *data, size_t *i, char c)
{
	size_t	start;

	start = *i;
	plus_pos(data->line, i, c);
	if (*i - start < 1)
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
			push_quote_element(data, &i, '"');
		if (data->line[i] == '\'')
			push_quote_element(data, &i, '\'');
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
	printf("\nsize is %zu\n", count_size(line, ' '));
	data.line = line;
	data.pos = 0;
	data.size = count_size(line, ' ');
	data.array = malloc(sizeof(char *) * (data.size + 1));
	if (data.array == NULL)
		return (NULL);
	data.array[data.size] = NULL;
	split_line(&data, ' ');
	int i = 0;
	while(data.array[i] != NULL)
	{
		printf("data is %s\n", data.array[i]);
		i++;
	}
	return (temp);
}
