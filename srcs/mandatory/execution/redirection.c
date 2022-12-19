/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:36:05 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/19 15:04:05 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/execution.h"

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

// void	change_file(t_list *comline)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*tmp;
// 	t_order	*order;

// 	order = (t_order *)comline->content;
// 	fd = open(order->file, O_RDONLY);
// 	if (fd == ERR)
// 		return ;
// 	tmp = order->file;
// 	make_tmp_file(order);
// 	fd2 = open(order->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd2 == ERR)
// 		exit (EXIT_FAILURE);
// 	free(tmp);
// 	close(fd);
// }

void	exec_ltlt(t_list *comline)
{
	int		fd;
	t_order	*order;
	t_order	*next_order;
	t_list	*next_piped_commands;

	order = (t_order *)comline->content;
	// change_file(comline);
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
