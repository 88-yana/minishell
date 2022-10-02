/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:11:28 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/01 17:34:11 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"



void	exec_export_with_no_args(t_list *envs_list)
{
	t_envs	*envs;

	while (envs_list)
	{
		envs = (t_envs *)envs_list->content;
		printf("declare -x %s=\"%s\"\n", envs->type, envs->value);
		envs_list = envs_list->next;
	}
}

void	exec_export(t_list *envs_list, char **cmd)
{
	size_t	i;
	t_envs	*envs;

	if (ft_strcmp(cmd[0], "export"))
		return ;
	if (cmd[1] == NULL)
		exec_export_with_no_args(envs_list);
	i = 1;
	//while (cmd[i])
	//{
	//	ft_strnstr(cmd[i], "+=", ft_strlen(cmd[i]));
	//	i++;
	//}
}

void	exec_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return ;
	printf("%s\n", cwd);
	free(cwd);
}

void	exec_builtin(t_list *envs_list, char **cmd)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		exec_export(envs_list, cmd);
}

bool	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (false);
	// if (!ft_strcmp(cmd[0], "echo"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "cd"))
	// 	return (true);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (true);
	else if (!ft_strcmp(cmd[0], "export"))
		return (true);
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "exit"))
	// 	return (true);
	else
		return (false);
}
