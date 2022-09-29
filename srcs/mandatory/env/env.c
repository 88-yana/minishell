/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:52:25 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 18:17:40 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/env.h"

t_envs	*get_envs(char *str)
{
	t_envs	*envs;
	char	*equal_address;

	envs = malloc(sizeof(t_envs));
	if (!envs)
		return (NULL);
	equal_address = ft_strchr(str, '=');
	envs->type = substr_size_t(str, 0, equal_address - str);
	envs->value = ft_strdup(equal_address + 1);
	if (!envs->type || !envs->value)
		return (NULL);
	return (envs);
}

void	create_envs_list(t_list **list, char *str)
{
	t_envs	*envs;
	t_list	*new_list;

	envs = get_envs(str);
	new_list = ft_lstnew(envs);
	if (!new_list)
		return ;
	if (list == NULL)
		*list = new_list;
	else
		ft_lstadd_back(list, new_list);
}

char	**get_envp_from_list(t_list *list)
{
	size_t	i;
	size_t	size;
	t_envs	*envs;
	char	**envp;

	size = count_lstsize(list);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envs = (t_envs *)list->content;
		envp[i] = strjoin_delimiter(envs->type, envs->value, "=");
		if (!envp[i])
			return (NULL);
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	convert_envp_to_list(t_vars *vars, char **envp)
{
	size_t	i;

	if (envp == NULL)
	{
		vars->envs_list = NULL;
		return ;
	}
	i = 0;
	while (envp[i])
	{
		create_envs_list(&vars->envs_list, envp[i]);
		i++;
	}
}
