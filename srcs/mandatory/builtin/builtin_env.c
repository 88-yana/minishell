/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:19:47 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/11 17:55:48 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/builtin.h"

void	exec_env(t_vars *vars)
{
	t_envs	*envs;
	t_list	*list;

	list = vars->envs;
	while (list)
	{
		envs = (t_envs *)list->content;
		if (envs->value)
			printf("%s=%s\n", envs->type, envs->value);
		list = list->next;
	}
}
