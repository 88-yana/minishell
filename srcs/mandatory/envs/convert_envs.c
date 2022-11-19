/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:35:11 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/19 21:39:33 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/envs.h"

void	convert_envp_to_list(t_vars *vars, char **envp)
{
	size_t	i;

	vars->envs = NULL;
	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		create_envs_list(vars, envp[i]);
		i++;
	}
}

char	**get_envp_from_list(t_list *list)
{
	size_t	i;
	size_t	list_size;
	t_envs	*envs;
	char	**envp;

	list_size = count_lstsize(list);
	envp = malloc(sizeof(char *) * (list_size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < list_size)
	{
		envs = (t_envs *)list->content;
		envp[i] = strjoin_delimiter(envs->type, envs->value, "=");
		if (envp[i] == NULL)
			return (NULL);
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
