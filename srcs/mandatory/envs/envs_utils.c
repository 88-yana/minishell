/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:52:25 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 20:59:32 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/envs.h"

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
	envs->value = ft_strjoin(buf, value);
	free(buf);
}

void	create_list(t_list **list, t_envs *envs)
{
	t_list	*new_list;

	new_list = ft_lstnew(envs);
	if (!new_list)
		return ;
	ft_lstadd_back(list, new_list);
}

void	create_envs_from_string(t_list **list, char *str)
{
	char	*type;
	char	*value;
	char	*equal;
	t_envs	*envs;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		type = ft_strdup(str);
		value = NULL;
	}
	else
	{
		type = substr_size_t(str, 0, equal - str);
		value = ft_strdup(equal + 1);
	}
	if (!type || !value)
		;
	envs = create_envs(type, value);
	if (!envs)
		;
	create_list(list, envs);
}

bool	create_envs_list(t_list **list, char *str)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (false);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=' || str[i] == '\0')
		create_envs_from_string(list, str);
	else if (str[i] == '+' && str[i + 1] == '=')
		return (true);
	else
		return (false);
	return (true);
}
