/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:36:05 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/05 16:43:15 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

void	exec_lt(t_vars *vars, t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	fd = check_file_and_open(vars, order);
	next_piped_commands = find_nth_piped_commands(comline, 1);
	if (!next_piped_commands)
		return ;
	next_order = (t_order *)next_piped_commands->content;
	if (fd == ERR)
	{
		next_order->can_exec = false;
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

void	exec_gt(t_vars *vars, t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	order->file = lexer_envs(vars, order->file);
	delete_quote(order->file);
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

void	exec_gtgt(t_vars *vars, t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	order->file = lexer_envs(vars, order->file);
	delete_quote(order->file);
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
