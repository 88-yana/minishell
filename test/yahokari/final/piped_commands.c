/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:19:17 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/24 17:34:39 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"

void	exec_command(t_vars *vars, char **command)
{
	execve(command[0], command, vars->envp);
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
	exit(0);
}

void	exec_command_child(t_vars *vars, t_list *comline, t_list **pids)
{
	pid_t	pid;
	t_order	*order;

	order = (t_order *)comline->content;
	pid = fork();
	if (pid == ERR) //need modified
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

// void	exec_command_parent(void)
// {
// 	;
// }
