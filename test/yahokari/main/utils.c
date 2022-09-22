/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:32:10 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/21 21:10:04 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

// t_list	*find_next_delimiters(t_list *list)
// {
// 	t_type	types[5];

// 	types[0] = COMMAND;
// 	types[1] = SHELL;
// 	types[2] = NULL;
// 	return (find_next_types(list, types));
// }

bool	is_next_pipe(t_list *list)
{
	t_list		*buf;
	t_comline	*order;

	buf = list->next;
	if (buf == NULL)
		return (false);
	order = (t_comline *)buf->content;
	if (order->type == PIPE)
		return (true);
	return (false);
}

t_list	*find_next_types(t_list *list, t_type *types)
{
	size_t		i;
	t_list		*buf;
	t_comline	*order;

	buf = list->next;
	while (buf)
	{
		order = (t_comline *)buf->content;
		i = 0;
		while (types[i])
		{
			if (order->type == types[i])
				return (buf);
			i++;
		}
		buf = buf->next;
	}
	return (NULL);
}

t_list	*find_next_piped_commands(t_list *list)
{
	t_list		*buf;
	t_comline	*order;

	buf = list->next;
	while (buf)
	{
		order = (t_comline *)buf->content;
		if (order->type == COMMAND || order->type == SHELL)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}
