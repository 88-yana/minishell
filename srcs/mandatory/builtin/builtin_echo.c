/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:29:40 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/09 10:25:16 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"builtin.h"

static bool	is_option_n(char *str)
{
	size_t	i;

	if (str == NULL || ft_strncmp(str, "-n", 2))
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	print_strs(char **cmd)
{
	size_t	i;

	i = 0;
	if (cmd[i] == NULL)
		return ;
	while (true)
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		i++;
		if (cmd[i] == NULL)
			break ;
		ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

void	exec_echo(char **cmd)
{
	size_t	i;
	bool	newline_flag;

	newline_flag = true;
	i = 1;
	g_status = 0;
	while (cmd[i])
	{
		if (!is_option_n(cmd[i]))
			break ;
		newline_flag = false;
		i++;
	}
	print_strs(&cmd[i]);
	if (newline_flag == true)
		printf("\n");
}
