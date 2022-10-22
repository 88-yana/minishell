/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:55:28 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/06 10:47:50 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/builtin.h"

static bool	is_overflow(long long value, int sign, char new_num)
{
	if (sign > 0 && value >= (LLONG_MAX / 10))
	{
		if (value == LLONG_MAX / 10
			&& value % 10 + (new_num - '0') <= LLONG_MAX % 10)
			return (false);
		return (true);
	}
	else if (sign < 0 && value >= -(LLONG_MIN / 10))
	{
		if (value == -(LLONG_MIN / 10)
			&& value % 10 + (new_num - '0') <= -(LLONG_MIN % 10))
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_exit_status_valid(const char *str)
{
	size_t		i;
	int			sign;
	long long	value;

	i = 0;
	value = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		if (is_overflow(value, sign, str[i]))
			return (false);
		value = 10 * value + (str[i] - '0');
		i++;
	}
	return (true);
}

static bool	exec_exit_with_numeric_args(char **cmd)
{
	if (cmd[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_status = 1;
		return (false);
	}
	g_status = ft_atoi(cmd[1]);
	return (true);
}

static void	exec_exit_with_not_numeric_args(char **cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	g_status = 255;
}

void	exec_exit(char **cmd)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd[1])
		g_status = 0;
	else
	{
		if (is_exit_status_valid(cmd[1]))
		{
			if (!exec_exit_with_numeric_args(cmd))
				return ;
		}
		else
			exec_exit_with_not_numeric_args(cmd);
	}
	exit(g_status);
}
