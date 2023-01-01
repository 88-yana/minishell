/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:31:32 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:45:19 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

bool	is_next_type(t_list *comline, t_type type)
{
	t_list	*buf;
	t_order	*order;

	buf = comline->next;
	if (buf == NULL)
		return (false);
	order = (t_order *)buf->content;
	if (order->type == type)
		return (true);
	return (false);
}

t_list	*find_next_delimiters(t_list *comline)
{
	t_list	*buf;
	t_order	*order;

	buf = comline->next;
	while (buf)
	{
		order = (t_order *)buf->content;
		if (order->type == AND || order->type == OR)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}

t_list	*find_nth_piped_commands(t_list *comline, size_t n)
{
	t_order	*order;
	size_t	count;

	count = 0;
	while (comline)
	{
		order = (t_order *)comline->content;
		if (order->type == COMMAND || order->type == SUBSHELL)
			count++;
		if (count == n)
			return (comline);
		comline = comline->next;
	}
	return (NULL);
}

t_list	*find_last_piped_commands(t_list *comline)
{
	t_order	*order;

	if (!comline)
		return (NULL);
	while (comline->next)
		comline = comline->next;
	order = (t_order *)comline->content;
	if (order->type == COMMAND || order->type == SUBSHELL)
		return (comline);
	return (NULL);
}
