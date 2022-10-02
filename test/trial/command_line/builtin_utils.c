/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:11:28 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/02 21:43:06 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"
#include	"limits.h"

void	exec_export_with_no_args(t_list *envs_list)
{
	t_envs	*envs;

	while (envs_list)
	{
		envs = (t_envs *)envs_list->content;
		printf("declare -x %s=\"%s\"\n", envs->type, envs->value);
		envs_list = envs_list->next;
	}
}

void	new_envs_list(t_list *envs_list, char *arg)
{
	t_envs	*envs;
	t_list	*buf;
	char	*equal_address;
	char	*type;
	char	*value;

	equal_address = ft_strchr(arg, '=');
	type = ft_substr(arg, 0, equal_address - arg);
	value = ft_strdup(equal_address + 1);
	buf = envs_list;
	while (buf)
	{
		envs = (t_envs *)buf->content;
		if (!ft_strcmp(envs->type, type))
		{
			free(type);
			free(envs->value);
			envs->value = value;
			return ;
		}
		buf = buf->next;
	}
	create_envs_list(&envs_list, arg);
	free(type);
	free(value);
}

void	add_to_envs_list(t_list *envs_list, char *arg)
{
	t_envs	*envs;
	t_list	*buf;
	char	*plus_address;
	char	*type;
	char	*value;
	char	*new_value;

	plus_address = ft_strchr(arg, '+');
	type = ft_substr(arg, 0, plus_address - arg);
	value = ft_strdup(plus_address + 2);
	buf = envs_list;
	while (buf)
	{
		envs = (t_envs *)buf->content;
		if (!ft_strcmp(envs->type, type))
		{
			free(type);
			new_value = ft_strjoin(envs->value, value);
			free(value);
			free(envs->value);
			envs->value = new_value;
			return ;
		}
		buf = buf->next;
	}
	create_envs_list(&envs_list, arg); //+= case
	free(type);
	free(value);
}

bool	check_argument(t_list *envs_list, char *arg)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(arg[i]) || arg[i] == '_'))
		return (false);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] == '=')
		new_envs_list(envs_list, arg);
	else if (arg[i] == '+' && arg[i + 1] == '=')
		add_to_envs_list(envs_list, arg);
	else
		return (false);
	return (true);
}

void	exec_export(t_list *envs_list, char **cmd)
{
	size_t	i;
	t_envs	*envs;

	if (ft_strcmp(cmd[0], "export"))
		return ;
	if (cmd[1] == NULL)
		exec_export_with_no_args(envs_list);
	i = 1;
	while (cmd[i])
	{
		if (!check_argument(envs_list, cmd[i]))
			ft_putendl_fd("minishell: export: `%s': not a valid identifier", 2);
		i++;
	}
}

static bool	ft_of(long long value, int sign, size_t i, const char *str)
{
	if (sign > 0 && value >= (LLONG_MAX / 10))
	{
		if (value == LLONG_MAX / 10
			&& value % 10 + (str[i] - '0') <= LLONG_MAX % 10)
			return (true);
		return (false);
	}
	else if (sign < 0 && value >= -(LLONG_MIN / 10))
	{
		if (value == -(LLONG_MIN / 10)
			&& value % 10 + (str[i] - '0') <= -(LLONG_MIN % 10))
			return (true);
		return (false);
	}
	return (true);
}

bool	is_exit_status_valid(const char *str)
{
	size_t		i;
	int			sign;
	long long	value;

	i = 0;
	value = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (!ft_strcmp("", &str[i]) || !ft_strcmp("+", &str[i])
		|| !ft_strcmp("-", &str[i]))
		return (false);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (!ft_of(value, sign, i, str))
			return (false);
		value = 10 * value + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (false);
	return (true);
}

void	exec_exit(char **cmd)
{
	if (ft_strcmp(cmd[0], "exit"))
		return ;
	ft_putendl_fd("exit", 2);
	if (cmd[1] == NULL)
		g_status = 0;
	else
	{
		if (is_exit_status_valid(cmd[1]))
		{
			if (cmd[2] == NULL)
				g_status = ft_atoi(cmd[1]);
			else
			{
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				g_status = 1;
				return ;
			}
		}
		else
		{
			ft_putendl_fd("minishell: exit: %s: numeric argument required", 2);
			g_status = 255;
		}
	}
	exit(g_status);
}

void	exec_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return ;
	printf("%s\n", cwd);
	free(cwd);
}

void	exec_env(t_list *envs_list, char **cmd)
{
	t_envs	*envs;

	if (ft_strcmp(cmd[0], "env"))
		return ;
	if (cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		return ;
	}
	while (envs_list)
	{
		envs = (t_envs *)envs_list->content;
		printf("%s=%s\n", envs->type, envs->value);
		envs_list = envs_list->next;
	}
}

void	exec_unset(t_list *envs_list, char **cmd)
{
	t_envs	*envs;

	while (envs_list)
	{
		envs = (t_envs *)envs_list->content;
		printf("%s=%s\n", envs->type, envs->value);
		envs_list = envs_list->next;
	}
}

void	exec_builtin(t_list *envs_list, char **cmd)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		exec_pwd();
	else if (!ft_strcmp(cmd[0], "export"))
		exec_export(envs_list, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		exec_env(envs_list, cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		exec_exit(cmd);
}

bool	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (false);
	// if (!ft_strcmp(cmd[0], "echo"))
	// 	return (true);
	// else if (!ft_strcmp(cmd[0], "cd"))
	// 	return (true);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (true);
	else if (!ft_strcmp(cmd[0], "export"))
		return (true);
	else if (!ft_strcmp(cmd[0], "env"))
		return (true);
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	return (true);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (true);
	else
		return (false);
}
