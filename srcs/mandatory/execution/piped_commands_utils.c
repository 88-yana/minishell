/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:22:39 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 14:46:06 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/execution.h"

void	set_fd(t_list *comline)
{
	t_order	*order;
	t_list	*next_command;
	int		buf[2];

	order = (t_order *)comline->content;
	if (is_next_type(comline, PIPE))
	{
		pipe(buf);
		order->next_read_fd = buf[0];
		next_command = find_nth_piped_commands(comline, 2);
		((t_order *)next_command->content)->read_fd = buf[0];
		if (order->write_fd != NONE)
			close(buf[1]);
		else
			order->write_fd = buf[1];
	}
}

void	duplicate_output(t_order *order)
{
	if (order->read_fd != NONE)
		dup2(order->read_fd, STDIN_FILENO);
	if (order->write_fd != NONE)
		dup2(order->write_fd, STDOUT_FILENO);
}

void	close_fd_child(t_order *order)
{
	if (order->read_fd != NONE)
		close(order->read_fd);
	if (order->write_fd != NONE)
		close(order->write_fd);
	if (order->next_read_fd != NONE)
		close(order->next_read_fd);
}

void	close_fd_parent(t_order *order)
{
	if (order->read_fd != NONE)
		close(order->read_fd);
	if (order->write_fd != NONE)
		close(order->write_fd);
	if (order->file)
		unlink(order->file);
}
