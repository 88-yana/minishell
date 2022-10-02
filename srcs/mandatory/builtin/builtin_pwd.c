/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:55:08 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/01 17:01:23 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"builtin.h"

void	exec_pwd(char **cmd)
{
	char	*cwd;

	if (ft_strcmp(cmd[0], "pwd"))
		return ;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return ;
	printf("%s\n", cwd);
	free(cwd);
}
