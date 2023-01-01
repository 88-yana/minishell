/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:43:42 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:44:34 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"builtin.h"

static void	print_cd_error(char *str, char *error)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_status = 1;
}

void	exec_cd(t_vars *vars, char **cmd)
{
	t_list	*home;
	t_list	*list;
	char	*dir;

	list = vars->envs;
	if (cmd[1] == NULL)
	{
		home = find_envs(list, "HOME");
		dir = ((t_envs *)home->content)->value;
	}
	else
		dir = cmd[1];
	if (dir == NULL)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	if (chdir(dir))
		print_cd_error(cmd[1], strerror(errno));
}
