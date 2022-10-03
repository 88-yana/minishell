/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:44:46 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 14:39:23 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"

void	set_env_pwd(t_list *envs_list, char **cmd)
{
	static int	initial_flag;

	if (initial_flag == 0)
	{
		create_envs_list(&envs_list, "OLDPWD=");
		initial_flag = 1;
	}
	// create_envs_list(&envs_list, cmd[]);
}

void	exec_cd(t_list *envs_list, char **cmd)
{
	char	*dir;

	if (!cmd[1])
		dir = find_env(envs_list, "HOME");
	else
		dir = cmd[1];
	if (!dir)
		ft_putendl_fd("minishell: cd: HOME not set\n", 2);
	chdir(dir);
}
