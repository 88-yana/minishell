/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/19 21:09:22 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

void	plus_pos(t_array *data, size_t *i, size_t *str_len, char c)
{
	go_advance(i, str_len);
	while (data->line[*i] != c)
		go_advance(i, str_len);
	go_advance(i, str_len);
	while (!is_separator(data->line[*i])
		&& data->line[*i] != SINGLEQ && data->line[*i] != DOUBLEQ)
		go_advance(i, str_len);
	if (is_separator(data->line[*i]))
		return ;
	if (data->line[*i] == DOUBLEQ)
		plus_pos(data, i, str_len, DOUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos(data, i, str_len, SINGLEQ);
	return ;
}

static void	push_element(t_array *data, size_t i, size_t len, int type)
{
	if (type == PUSHELEM)
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
		if (data->line[i] == DOUBLEQ)
			plus_pos(data, &i, &str_len, DOUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_pos(data, &i, &str_len, SINGLEQ);
		if (type == CNTSTRLEN)
			data->strs_len[data->pos] = str_len + 1;
		if (is_separator(data->line[i]) && str_len > 0)
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

// char	**lexer(char *line)
// {
// 	t_array	data;
// 	char	**array;

// 	data.line = line;
// 	if (check_line(data.line) == false)
// 		return (NULL);
// 	if (malloc_array(&data) == NULL)
// 		return (NULL);
// 	// if (malloc_element(&data) == NULL)
// 	// 	return (NULL);
// 	// data.pos = 0;
// 	// split_line(&data, PUSHELEM);
// 	// array = divide_redirect(data.array);
// 	return (array);
// }

char	**lexer(char *line)
{
	t_array	data;
	char	**array;

	data.line = line;
	if (check_line(data.line) == false)
		return (NULL);
	if (malloc_array(&data) == NULL)
		return (NULL);
	if (malloc_element(&data) == NULL)
		return (NULL);
	data.pos = 0;
	split_line(&data, PUSHELEM);
	free(data.strs_len);
	array = divide_redirect(data.array);
	return (data.array);
}

int	main(void)
{
	char	**array;
	int		i;

	array = lexer("abc def ghi");
	i = 0;
	// while (i < 2)
	// {
	// 	printf("%s\n", array[i]);
	// 	i++;
	// }

	system("leaks -q a.out");
}
