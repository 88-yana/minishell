/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:46:59 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/05 21:11:28 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

bool	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd[0], "echo"))
		return (true);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (true);
	if (!ft_strcmp(cmd[0], "pwd"))
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

void	exec_builtin(t_vars *vars, char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		exec_echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		exec_cd(vars->envs, cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exec_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		exec_export(vars->envs, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		exec_unset(vars, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		exec_env(vars->envs, cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		exec_exit(cmd);
}
