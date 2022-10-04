/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:00:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 21:01:47 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

static void	exec_export_with_no_args(t_list *list)
{
	t_envs	*envs;

	while (list)
	{
		envs = (t_envs *)list->content;
		if (!envs->value)
			printf("declare -x %s\n", envs->type);
		else
			printf("declare -x %s=\"%s\"\n", envs->type, envs->value);
		list = list->next;
	}
}

static void	print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	g_status = 1;
}

void	exec_export(t_list *list, char **cmd)
{
	size_t	i;
	t_envs	*envs;

	g_status = 0;
	if (cmd[1] == NULL)
		exec_export_with_no_args(list);
	i = 1;
	while (cmd[i])
	{
		if (!create_envs_list(&list, cmd[i]))
			print_export_error(cmd[i]);
		i++;
	}
}
