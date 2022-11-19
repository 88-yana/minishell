/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:41:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/19 20:34:38 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer_two_symbols.h"

t_array	*malloc_array_re(t_array *data)
{
	data->pos = 0;
	split_line_re(data, 0);
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

t_array	*malloc_element_re(t_array *data)
{
	size_t	i;

	data->pos = 0;
	split_line_re(data, 1);
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
