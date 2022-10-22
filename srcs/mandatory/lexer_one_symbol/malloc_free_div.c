/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_div.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:41:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/22 18:17:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_one_symbol.h"

static void	free_array(t_array *data)
{
	size_t	i;

	i = 0;
	while (i < data->pos)
	{
		free(data->array[i]);
		i++;
	}
	free(data->array);
}

t_array	*malloc_array_div(t_array *data)
{
	data->pos = 0;
	split_line_div(data, 0);
	data->array = malloc(sizeof(char *) * (data->pos + 1));
	data->strs_len = malloc(sizeof(size_t) * data->pos);
	if (data->array == NULL || data->strs_len == NULL)
	{
		free(data->array);
		free(data->strs_len);
		perror("malloc failed");
		return (NULL);
	}
	data->array[data->pos] = NULL;
	return (data);
}

t_array	*malloc_element_div(t_array *data)
{
	size_t	i;

	data->pos = 0;
	split_line_div(data, 1);
	i = 0;
	while (i < data->pos)
	{
		data->array[i] = malloc(data->strs_len[i]);
		if (data->array[i] == NULL)
		{
			free_array(data);
			free(data->strs_len);
			perror("malloc failed");
			return (NULL);
		}
		i++;
	}
	return (data);
}
