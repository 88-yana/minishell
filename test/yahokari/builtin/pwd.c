/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:19:12 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 19:50:43 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"builtin.h"

void	exec_pwd(t_vars *vars)
{
	t_list	*list;
	t_envs	*envs;

	list = vars->envs_list;
	while (list)
	{
		envs = (t_envs *)list->content;
		if (!ft_strcmp(envs->type, "PWD"))
		{
			printf("%s\n", envs->value);
			break ;
		}
		list = list->next;
	}
}
