/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:33:09 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/17 19:34:49 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/envs.h"

void	convert_envp_to_list(t_vars *vars, char **envp)
{
	size_t	i;

	vars->envs = NULL;
	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		create_envs_list(&vars->envs, envp[i]);
		i++;
	}
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
