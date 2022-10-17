/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:29:46 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/17 21:30:53 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/envs.h"

t_envs	*create_envs(char *type, char *value)
{
	t_envs	*envs;

	envs = malloc(sizeof(t_envs));
	if (!envs)
		return (NULL);
	envs->type = type;
	envs->value = value;
	return (envs);
}

void	add_to_envs(t_envs *envs, char *value)
{
	char	*buf;

	buf = envs->value;
	if (!buf)
		envs->value = value;
	else
	{
		envs->value = ft_strjoin(buf, value);
		free(buf);
	}
}

void	replace_envs(t_envs *envs, char *value)
{
	char	*buf;

	buf = envs->value;
	envs->value = value;
	free(buf);
}

void	free_envs(void *p)
{
	t_envs	*envs;

	envs = (t_envs *)p;
	free(envs->type);
	free(envs->value);
	free(envs);
}

void	create_list(t_list **list, t_envs *envs)
{
	t_list	*new_list;

	new_list = ft_lstnew(envs);
	if (!new_list)
		return ;
	ft_lstadd_back(list, new_list);
}
