/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:36:05 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:44:02 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution_bonus.h"

void	exec_lt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = open(order->file, O_RDONLY);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	if (!next_piped_commands)
		return ;
	next_order = (t_order *)next_piped_commands->content;
	if (fd == ERR)
	{
		next_order->can_exec = false;
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(order->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_status = 1;
		return ;
	}
	if (next_order->read_fd != NONE)
		close(next_order->read_fd);
	next_order->read_fd = fd;
	if (next_order->file)
		unlink(next_order->file);
}

void	exec_ltlt(t_vars *vars, t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	if (!order->is_quote)
		change_file(vars, comline);
	fd = open(order->file, O_RDONLY);
	if (fd == ERR)
		exit (EXIT_FAILURE);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	if (!next_piped_commands)
		return ;
	next_order = (t_order *)next_piped_commands->content;
	if (next_order->read_fd != NONE)
		close(next_order->read_fd);
	next_order->read_fd = fd;
	if (next_order->file)
		unlink(next_order->file);
	next_order->file = order->file;
}

void	exec_gt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = open(order->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == ERR)
		exit (EXIT_FAILURE);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	if (!next_piped_commands)
		return ;
	next_order = (t_order *)next_piped_commands->content;
	if (next_order->write_fd != NONE)
		close(next_order->write_fd);
	next_order->write_fd = fd;
}

void	exec_gtgt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = open(order->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == ERR)
		exit (EXIT_FAILURE);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	if (!next_piped_commands)
		return ;
	next_order = (t_order *)next_piped_commands->content;
	if (next_order->write_fd != NONE)
		close(next_order->write_fd);
	next_order->write_fd = fd;
}
