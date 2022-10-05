/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:10:29 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/05 21:15:28 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

bool	is_str_valid_list(char *str)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (false);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=' || str[i] == '\0')
		return (true);
	else if (str[i] == '+' && str[i + 1] == '=')
		return (true);
	else
		return (false);
}

// void	delete_env(t_list **list, char *type)
// {
// 	t_envs	*envs;
// 	t_list	*buf;
// 	t_list	*cur;

// 	printf("%p\n", *list);
// 	if (!list || !is_str_valid_list(type))
// 		return ;
// 	cur = *list;
// 	envs = (t_envs *)cur->content;
// 	if (!cur->next && !ft_strcmp(envs->type, type))
// 	{
// 		ft_lstdelone(cur, delete_envs);
// 		*list = NULL;
// 	}
// 	if (!ft_strcmp(envs->type, type))
// 	{
// 		printf("%p\n", *list);
// 		buf = cur->next;
// 		ft_lstdelone(*list, delete_envs);
// 		list = &buf;
// 		printf("%p\n", *list);
// 		return ;
// 	}
// 	while (cur->next)
// 	{
// 		envs = (t_envs *)cur->next->content;
// 		if (!ft_strcmp(envs->type, type))
// 		{
// 			buf = cur->next->next;
// 			ft_lstdelone(cur->next, delete_envs);
// 			cur->next = buf;
// 			break ;
// 		}
// 		cur = cur->next;
// 	}
// }

void	delete_envs_single_top(t_list **list, char *type)
{
	ft_lstdelone(*list, free_envs);
	*list = NULL;
}

void	delete_envs_top(t_vars *vars, char *type)
{
	t_list	*buf;

	buf = vars->envs->next;
	ft_lstdelone(vars->envs, free_envs);
	vars->envs = buf;
}

void	delete_envs_not_top(t_list *list, char *type)
{
	t_envs	*envs;
	t_list	*buf;

	while (list->next)
	{
		envs = (t_envs *)list->next->content;
		if (!ft_strcmp(envs->type, type))
		{
			buf = list->next->next;
			ft_lstdelone(list->next, free_envs);
			list->next = buf;
			break ;
		}
		list = list->next;
	}
}

void	delete_envs(t_vars *vars, char *type)
{
	t_envs	*envs;
	t_list	*list;

	if (!is_str_valid_list(type))
		return ;
	list = vars->envs;
	envs = (t_envs *)list->content;
	if (!list->next && !ft_strcmp(envs->type, type))
		delete_envs_single_top(&list, type);
	else if (!ft_strcmp(envs->type, type))
		delete_envs_top(vars, type);
	else
		delete_envs_not_top(list, type);
}

void	exec_unset(t_vars *vars, char **cmd)
{
	size_t	i;

	i = 1;
	while (cmd[i])
	{
		delete_envs(vars, cmd[i]);
		i++;
	}
}
