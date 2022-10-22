/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:30:51 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 18:59:00 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide_quote.h"
#include "../../lexer/lexer.h"

//"     "<<"       "
//hello
//echo << hello
bool	push_element_quo(t_array *data, size_t i, size_t len, int type)
{
	if (is_null(data->line[i]) == false)
		return (false);
	if (type == 2)
		if (data->line[i] == '\0')
			ft_strlcpy(data->array[data->pos], &(data->line[i - len]), len + 1);
	data->pos++;
	return (true);
}

static void	copy_redirect(t_array *data, size_t *i, size_t *len)
{
	ft_strlcpy(data->array[data->pos], &(data->line[*i - *len]), *len + 1);
	ft_strlcpy(data->array[data->pos + 1], &(data->line[*i]), 3);
}

// <<
// echo << hello <<
bool	push_element_re(t_array *data, size_t *i, size_t *len, int type)
{
	if (is_separator_re(data->line[*i], data->line[*i + 1]) == false)
	{
		(*len)++;
		return (false);
	}
	else if (i == 0)
	{
		if (type == 2)
			ft_strlcpy(data->array[data->pos], &(data->line[*i - *len]), 3);
		data->pos++;
	}
	else
	{
		if (type == 2)
			copy_redirect(data, i, len);
		data->pos += 2;
	}
	if (is_null(data->line[*i + 2]))
		return (true);
	*len = 0;
	(*i)++;
	return (false);
}
