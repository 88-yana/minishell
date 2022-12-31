/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:36:05 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 14:49:00 by yahokari         ###   ########.fr       */
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

void	chenage_file_with_env(t_vars *vars, int fd_from, int fd_to)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd_from);
		if (!line)
			break ;
		line = lexer_envs(vars, line);
		ft_putstr_fd(line, fd_to);
		free(line);
	}
}

void	change_file(t_vars *vars, t_list *comline)
{
	int		fd_from;
	int		fd_to;
	char	*tmp;
	t_order	*order;

	order = (t_order *)comline->content;
	fd_from = open(order->file, O_RDONLY);
	if (fd_from == ERR)
		exit (EXIT_FAILURE);
	tmp = order->file;
	make_tmp_file(order);
	fd_to = open(order->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_to == ERR)
		exit (EXIT_FAILURE);
	chenage_file_with_env(vars, fd_from, fd_to);
	close(fd_from);
	close(fd_to);
	unlink(tmp);
	free(tmp);
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
