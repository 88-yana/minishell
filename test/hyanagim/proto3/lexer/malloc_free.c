/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:41:52 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/29 21:54:17 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../../../minishell/include/lexer.h" 
#include "../../../trial/main/main.h"

void	split_line(t_array *data, int type);

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

t_array	*malloc_array(t_array *data)
{
	data->pos = 0;
	split_line(data, 0);
	data->array = malloc(sizeof(char *) * (data->pos + 1));
	data->length = malloc(sizeof(size_t) * data->pos);
	if (data->array == NULL || data->length == NULL)
	{
		free(data->array);
		free(data->length);
		perror("malloc failed");
		return (NULL);
	}
	data->array[data->pos] = NULL;
	return (data);
}

t_array	*malloc_element(t_array *data)
{
	size_t	i;

	data->pos = 0;
	split_line(data, 1);
	i = 0;
	while (i < data->pos)
	{
		data->array[i] = malloc(data->length[i]);
		if (data->array[i] == NULL)
		{
			free_array(data);
			free(data->length);
			perror("malloc failed");
			return (NULL);
		}
		i++;
	}
	return (data);
}
