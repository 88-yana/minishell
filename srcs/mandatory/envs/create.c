/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:27:18 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 11:45:50 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/envs.h"

static void	safe_free_envs(t_envs *envs)
{
	free(envs->type);
	free(envs->value);
	envs->type = NULL;
	envs->value = NULL;
}

void	add_to_envs_list(t_vars *vars, char *str)
{
	char	*plus;
	t_envs	input;
	t_envs	*envs;
	t_list	*list;

	plus = ft_strchr(str, '+');
	input.type = substr_size_t(str, 0, plus - str);
	input.value = ft_strdup(plus + 2);
	if (!input.type || !input.value)
		return (safe_free_envs(&input));
	list = find_envs(vars->envs, input.type);
	if (list)
		add_to_envs(list->content, input.value);
	else
	{
		envs = create_envs(input.type, input.value);
		if (!envs)
			return (safe_free_envs(&input));
		create_list(&vars->envs, envs);
	}
}

static t_envs	check_envs_input(t_vars *vars, char *str)
{
	char	*equal;
	t_envs	input;

	equal = ft_strchr(str, '=');
	if (!equal)
	{
		input.type = ft_strdup(str);
		input.value = NULL;
		if (!input.type || find_envs(vars->envs, input.type))
			safe_free_envs(&input);
	}
	else
	{
		input.type = substr_size_t(str, 0, equal - str);
		input.value = ft_strdup(equal + 1);
		if (!input.type || !input.value)
			safe_free_envs(&input);
	}
	return (input);
}

void	create_new_envs_list(t_vars *vars, char *str)
{
	t_envs	input;
	t_envs	*envs;
	t_list	*list;

	input = check_envs_input(vars, str);
	if (!input.type && !input.value)
		return ;
	list = find_envs(vars->envs, input.type);
	if (list)
	{
		replace_envs(list->content, input.value);
		free(input.type);
	}
	else
	{
		envs = create_envs(input.type, input.value);
		if (!envs)
			return (safe_free_envs(&input));
		create_list(&vars->envs, envs);
	}
}

bool	create_envs_list(t_vars *vars, char *str)
{
	t_list	*list;
	size_t	i;

	i = 0;
	list = vars->envs;
	if (!str)
		return (false);
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (false);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=' || str[i] == '\0')
		create_new_envs_list(vars, str);
	else if (str[i] == '+' && str[i + 1] == '=')
		add_to_envs_list(vars, str);
	else
		return (false);
	return (true);
}
