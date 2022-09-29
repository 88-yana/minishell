/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:11:28 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 21:50:51 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"

void	exec_pwd(t_vars *vars)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return ;
	printf("%s\n", cwd);
	free(cwd);
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
	// else if (!ft_strcmp(cmd[0], "export"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "exit"))
	// 	return (true);
	else
		return (false);
}
