/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:32:35 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 18:54:39 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"env.h"

t_envs	*get_envs(char *str)
{
	t_envs	*envs;
	char	*equal_address;
	size_t	len;

	envs = malloc(sizeof(t_envs));
	if (!envs)
		return (NULL);
	equal_address = ft_strchr(str, '=');
	len = ft_strlen(str);
	envs->type = ft_substr(str, 0, equal_address - str);
	envs->value = ft_strdup(equal_address + 1);
	return (envs);
}

void	create_envs_list(t_list **list, char *str)
{
	t_envs	*envs;

	envs = get_envs(str);
	if (list == NULL)
		*list = ft_lstnew(envs);
	else
		ft_lstadd_back(list, ft_lstnew(envs));
}

size_t	count_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	if (lst == NULL)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**get_envp_from_list(t_list *list)
{
	size_t	i;
	size_t	size;
	t_envs	*envs;
	char	**envp;
	char	*buf;

	size = count_lstsize(list);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
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
