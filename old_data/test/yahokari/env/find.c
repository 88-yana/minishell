/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:15:31 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/26 18:20:35 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"env.h"

char	*find_env(t_list *list, char *to_find)
{
	t_envs	*envs;

	if (!list || !to_find)
		return (NULL);
	while (list)
	{
		envs = (t_envs *)list->content;
		if (!ft_strcmp(envs->type, to_find))
			return (envs->value);
		list = list->next;
	}
	return (NULL);
}
