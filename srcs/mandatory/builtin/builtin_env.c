/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:19:47 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/04 21:26:59 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

void	exec_env(t_list *list, char **cmd)
{
	t_envs	*envs;

	while (list)
	{
		envs = (t_envs *)list->content;
		if (envs->value)
			printf("%s=%s\n", envs->type, envs->value);
		list = list->next;
	}
}
