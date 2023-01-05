/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:22:39 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/05 15:28:34 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

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

void	check_envs_from_path(t_vars *vars, char **command)
{
	char	**path;
	t_list	*list;

	list = find_envs(vars->envs, "PATH");
	if (!list)
		path = NULL;
	else
		path = ft_split(((t_envs *)list->content)->value, ':');
	if (!check_path(path, command))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	if (path)
		safe_free_double_char(path);
}
