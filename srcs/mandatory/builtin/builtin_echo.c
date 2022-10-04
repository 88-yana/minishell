/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:29:40 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/03 11:52:39 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

static bool	is_option_n(char *str)
{
	size_t	i;

	if (!str || ft_strncmp(str, "-n", 2))
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
	while (true)
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i] == NULL)
			break ;
		printf(" ");
	}
}

void	exec_echo(char **cmd)
{
	size_t	i;
	bool	newline_flag;

	newline_flag = true;
	i = 1;
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
