/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_re.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:53:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/04 14:47:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide_quote.h"
#include "../../lexer/lexer.h"

static void	plus_pos_re(t_array *data, size_t *i, size_t *str_len, char c)
{
	go_advance(i, str_len);
	while (data->line[*i] != c)
		go_advance(i, str_len);
	go_advance(i, str_len);
	while (!is_separator_re(data->line[*i], data->line[*i + 1])
		&& data->line[*i] != SINGLEQ && data->line[*i] != DUBLEQ)
		go_advance(i, str_len);
	if (is_separator_re(data->line[*i], data->line[*i + 1]))
		return ;
	if (data->line[*i] == DUBLEQ)
		plus_pos_re(data, i, str_len, DUBLEQ);
	if (data->line[*i] == SINGLEQ)
		plus_pos_re(data, i, str_len, SINGLEQ);
	return ;
}

static void	push_element_re(t_array *data, size_t i, size_t len, int type)
{
	if (ft_strlen(data->line) > 1 && data->line[i + 1] == '\0')
		if (is_ltltgtgt(data->line[i -1], data->line[i]))
			return ;
	// printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	if (type == 2)
	{
		if (data->line[i] == '\0')
			ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 1);
		else if (data->line[i + 1] == '\0')
			ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 2);
		else if (i == 0)
			ft_strlcpy(data->array[data->pos], &(data->line[i]), 3);
		else
		{
			ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 1);
			ft_strlcpy(data->array[data->pos + 1], &(data->line[i]), 3);
		}
	}
	if (data->line[i] == '\0')
		data->pos++;
	else if (data->line[i + 1] == '\0')
			data->pos++;
	else if (i == 0)
		data->pos++;
	else
		data->pos += 2;
}

void	split_line_re(t_array *data, int type)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	while (1)
	{
		if (data->line[i] == DUBLEQ)
		{
			plus_pos(data, &i, &str_len, DUBLEQ);
			// data->pos++;
		}
		if (data->line[i] == SINGLEQ)
			plus_pos(data, &i, &str_len, SINGLEQ);
		// printf("c is %c\n", data->line[i]);
		if (data->line[i] == '\0')
			// printf("空白\n");
		// printf("len is %d\n", str_len);
		if (type == 1)
			data->length[data->pos] = str_len + 1;
		if (data->line[i] == '\0' || is_separator_re(data->line[i], data->line[i + 1]))
		{
			// printf("in\n");
			push_element_re(data, i, str_len, type);
			str_len = 0;
			i++;
		}
		else
			str_len++;
		// printf("size is %zu\n", data->pos);
		if (data->line[i + 1] == '\0')
			break ;
		i++;
	}
}

char	**lexer_re(t_array	*data)
{
	if (malloc_array_re(data) == NULL)
		return (NULL);
	if (malloc_element_re(data) == NULL)
		return (NULL);
	data->pos = 0;
	split_line_re(data, 2);
	return (data->array);
}

// int	main(void)
// {
// 	t_array	data;
// 	char	**array;

// 	while (true)
// 	{
// 		data.line = exec_readline();
// 		if (data.line == NULL)
// 			continue ;
// 		array = lexer_re(&data);
// 		if (array == NULL)
// 			continue ;
// 		size_t i = 0;
// 		while (array[i] != NULL)
// 		{
// 			printf("「%s」\n", array[i]);
// 			i++;
// 		}
// 	}
// }

//abc<<def<<abcabcabc>>bbbeeebbb>>bbb"eeeggg<<"aaa<<bbbcc<cc
//echo "" "      " akj<<alkfj << salkdfj
//<<abc"     " abcd abc "    " "     "'abc'd  abc<<abc<<