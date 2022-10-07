/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:43:42 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/07 21:26:43 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

static char	*get_dir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	return (cwd);
}

static void	set_env_oldpwd(t_list *list, char **cmd)
{
	static int	initial_flag;
	t_list		*old_wd;
	char		*dir;
	char		*buf;

	old_wd = find_envs(list, "OLDPWD");
	dir = get_dir();
	if (!dir)
		return ;
	if (initial_flag == 0 && !old_wd)
	{
		buf = strjoin_delimiter("OLDPWD", dir, "=");
		free(dir);
		create_envs_list(&list, buf);
		initial_flag = 1;
		return ;
	}
	if (!old_wd)
		return ;
	free(((t_envs *)old_wd->content)->value);
	((t_envs *)old_wd->content)->value = dir;
}

static void	set_env_pwd(t_list *list, char **cmd)
{
	static int	initial_flag;
	t_list		*cwd;
	char		*dir;

	cwd = find_envs(list, "PWD");
	dir = get_dir();
	if (!dir || !cwd)
		return ;
	free(((t_envs *)cwd->content)->value);
	((t_envs *)cwd->content)->value = dir;
}

void	exec_cd(t_vars *vars, char **cmd)
{
	t_list	*home;
	t_list	*list;
	char	*dir;

	list = vars->envs;
	if (!cmd[1])
	{
		home = find_envs(list, "HOME");
		dir = ((t_envs *)home->content)->value;
	}
	else
		dir = cmd[1];
	if (!dir)
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	set_env_oldpwd(list, cmd);
	chdir(dir);
	set_env_pwd(list, cmd);
}
