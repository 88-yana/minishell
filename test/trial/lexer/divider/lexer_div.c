/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_div.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/04 15:48:45 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide.h"
#include "../../lexer/lexer.h"

static void	plus_pos_div(t_array *data, size_t *i, size_t *str_len, char c)
{
	go_advance(i, str_len);
	while (data->line[*i] != c)
		go_advance(i, str_len);
	go_advance(i, str_len);
	while (!is_separator_div(data->line[*i])
		&& data->line[*i] != SINGLEQ && data->line[*i] != DUBLEQ)
		go_advance(i, str_len);
	if (is_separator_div(data->line[*i]))
		return ;
	if (data->line[*i] == DUBLEQ)
		plus_pos_div(data, i, str_len, DUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos_div(data, i, str_len, SINGLEQ);
	return ;
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
		printf("%s\n", &(data->line[i - len]));
		printf("in type 2 return : 『%s』\n", data->array[0]);
	}
	if (data->line[i] == '\0')
	{
		data->pos++;
	}
	else if (i == 0)
		data->pos++;
	else
		data->pos += 2;
}

void	split_line_div(t_array *data, int type)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DUBLEQ)
			plus_pos_div(data, &i, &str_len, DUBLEQ);
		if (data->line[i] == SINGLEQ)
			plus_pos_div(data, &i, &str_len, SINGLEQ);
		if (type == 1)
			data->length[data->pos] = str_len + 1;
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
	printf("brefore return : %s\n", data->array[0]);
	return (data->array);
}

// int	main(void)
// {
// 	t_array	data;
// 	char	**array;
// 	size_t	i;

// 	while (true)
// 	{
// 		data.line = exec_readline();
// 		if (data.line == NULL)
// 			continue ;
// 		array = lexer_div(&data);
// 		if (array == NULL)
// 			continue ;
// 		array = delete_brank(array);
// 		i = 0;
// 		while (array[i] != NULL)
// 		{
// 			printf("「%s」\n", array[i]);
// 			if (array[i][0] == '\0')
// 				printf("%s\n", "空白");
// 			i++;
// 		}
// 	}
// 	return (0);
// }

//abc<<def<<abcabcabc>>bbbeeebbb>>bbb"eeeggg<<"aaa<<bbbcc<cc