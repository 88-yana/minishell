/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_unlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:47:48 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/04 23:59:30 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

void	heredoc_unlink(t_list *comline, t_list *end)
{
	t_list	*buf;
	t_order	*order;

	buf = comline;
	while (buf)
	{
		order = (t_order *)buf->content;
		if (order->type == LTLT)
			unlink(order->file);
		if (buf == end)
			break ;
		buf = buf->next;
	}
}
