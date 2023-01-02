/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:32:06 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:44:24 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"envs_bonus.h"

t_list	*find_envs(t_list *list, char *to_find)
{
	t_envs	*envs;

	if (!list || !to_find)
		return (NULL);
	while (list)
	{
		envs = (t_envs *)list->content;
		if (!ft_strcmp(envs->type, to_find))
			return (list);
		list = list->next;
	}
	return (NULL);
}
