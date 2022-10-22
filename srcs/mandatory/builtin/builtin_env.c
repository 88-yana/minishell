/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:19:47 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/22 19:25:58 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/builtin.h"

void	exec_env(t_vars *vars, char **cmd)
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
