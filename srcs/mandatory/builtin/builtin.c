/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:46:59 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/09 10:51:46 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"builtin.h"

bool	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd[0], "echo"))
		return (true);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (true);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (true);
	else if (!ft_strcmp(cmd[0], "export"))
		return (true);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (true);
	else if (!ft_strcmp(cmd[0], "env"))
		return (true);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (true);
	else
		return (false);
}

void	exec_builtin(t_vars *vars, char **cmd, bool is_pipe)
{
	if (!ft_strcmp(cmd[0], "echo"))
		exec_echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		exec_cd(vars, cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		exec_export(vars, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		exec_unset(vars, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		exec_env(vars);
	else if (!ft_strcmp(cmd[0], "exit"))
		exec_exit(cmd, is_pipe);
}

void	exec_single_builtin(t_vars *vars, t_order *order)
{
	int		tmp;

	tmp = dup(STDOUT_FILENO);
	if (order->write_fd != NONE)
	{
		dup2(order->write_fd, STDOUT_FILENO);
		close(order->write_fd);
	}
	exec_builtin(vars, order->cmd, false);
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	if (order->file)
		unlink(order->file);
}
