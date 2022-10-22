/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_envs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:35:11 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 12:06:30 by yahokari         ###   ########.fr       */
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
	char	*buf;

	list_size = count_lstsize(list);
	envp = malloc(sizeof(char *) * (list_size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < list_size)
	{
		envs = (t_envs *)list->content;
		buf = ft_strjoin(envs->type, "=");
		envp[i] = ft_strjoin(buf, envs->value);
		free(buf);
		list = list->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
