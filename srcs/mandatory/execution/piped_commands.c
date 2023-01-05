/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:57:18 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/05 15:29:08 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

void	check_command(t_vars *vars, char ***command)
{
	size_t	i;

	i = 0;
	while ((*command)[i])
	{
		(*command)[i] = lexer_envs(vars, (*command)[i]);
		i++;
	}
	*command = check_asterisk(*command);
	i = 0;
	while ((*command)[i])
	{
		delete_quote((*command)[i]);
		i++;
	}
}

bool	check_path(char **path, char **command)
{
	size_t	i;
	char	*tmp;
	char	*buf;

	if (!access(command[0], F_OK))
		return (true);
	else if (!path)
		return (false);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		buf = ft_strjoin(tmp, command[0]);
		free(tmp);
		if (!access(buf, F_OK))
		{
			command[0] = buf;
			return (true);
		}
		free(buf);
		i++;
	}
	return (false);
}

void	exec_command(t_vars *vars, char **command)
{
	char	**envp;

	if (is_builtin(command))
	{
		exec_builtin(vars, command);
		exit(g_status);
	}
	check_envs_from_path(vars, command);
	envp = get_envp_from_list(vars->envs);
	execve(command[0], command, envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	safe_free_double_char(envp);
	exit(126);
}

void	exec_subshell(t_list *comline, t_vars *vars)
{
	t_order	*order;
	t_list	*next_command;
	t_list	*last_command;
	t_order	*next_order;
	t_order	*last_order;

	order = (t_order *)comline->content;
	next_command = find_nth_piped_commands(order->shell, 1);
	next_order = next_command->content;
	next_order->read_fd = order->read_fd;
	last_command = find_last_piped_commands(next_command);
	last_order = last_command->content;
	last_order->write_fd = order->write_fd;
	last_order->next_read_fd = order->next_read_fd;
	exec_comline(vars, order->shell);
	exit(g_status);
}

void	exec_command_child(t_vars *vars, t_list *comline, t_list **pids)
{
	pid_t	pid;
	t_order	*order;

	order = (t_order *)comline->content;
	pid = fork();
	if (pid == ERR)
		exit (EXIT_FAILURE);
	else if (pid == CHILD)
	{
		if (order->type == COMMAND)
		{
			duplicate_output(order);
			close_fd_child(order);
			exec_command(vars, order->cmd);
		}
		else if (order->type == SUBSHELL)
			exec_subshell(comline, vars);
	}
	create_pid_list(pids, pid);
}
