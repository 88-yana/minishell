/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:26:16 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/17 21:34:03 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

static bool	is_str_valid_list(char *str)
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

void	delete_envs_single_top(t_vars *vars, char *type)
{
	ft_lstdelone(vars->envs, free_envs);
	vars->envs = NULL;
}

void	delete_envs_top(t_vars *vars, char *type)
{
	t_list	*list;
	t_list	*buf;

	list = vars->envs;
	if (list->next)
		buf = list->next;
	else
		buf = NULL;
	ft_lstdelone(list, free_envs);
	vars->envs = buf;
}

static void	delete_envs_not_top(t_vars *vars, char *type)
{
	t_envs	*envs;
	t_list	*list;
	t_list	*buf;

	list = vars->envs;
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

static void	delete_envs(t_vars *vars, char *type)
{
	t_envs	*envs;
	t_list	*list;

	if (!is_str_valid_list(type))
		return ;
	list = vars->envs;
	envs = (t_envs *)list->content;
	if (!list->next && !ft_strcmp(envs->type, type))
		delete_envs_single_top(vars, type);
	else if (!ft_strcmp(envs->type, type))
		delete_envs_top(vars, type);
	else
		delete_envs_not_top(vars, type);
}

void	exec_unset(t_vars *vars, char **cmd)
{
	size_t	i;

	g_status = 0;
	i = 1;
	if (!vars->envs)
		return ;
	while (cmd[i])
	{
		delete_envs(vars, cmd[i]);
		i++;
	}
}
