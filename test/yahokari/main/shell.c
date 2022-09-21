/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:39:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/21 21:32:44 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	exec_ve(char **command, t_vars *vars)
{
	execve(command[0], command, vars->envp);
}

void	set_fd(t_list *list)
{
	t_comline	*comline;
	t_list		*next_command;
	int			buf[2];

	comline = (t_comline *)list->content;
	if (is_next_pipe(list))
	{
		pipe(buf);
		comline->next_read_fd = buf[0];
		next_command = find_next_piped_commands(list);
		((t_comline *)next_command->content)->read_fd = buf[0];
		if (comline->write_fd != -1)
			close(buf[1]);
		else
			comline->write_fd = buf[1];
	}
}

void	close_fd_child(t_comline *comline)
{
	if (comline->read_fd != -1)
		close(comline->read_fd);
	if (comline->write_fd != -1)
		close(comline->write_fd);
	if (comline->next_read_fd != -1)
		close(comline->next_read_fd);
}

void	duplicate_output(t_comline *comline)
{
	if (comline->read_fd != -1)
		dup2(comline->read_fd, STDIN_FILENO);
	if (comline->write_fd != -1)
		dup2(comline->write_fd, STDOUT_FILENO);
}

void	close_fd_parent(t_comline *comline)
{
	if (comline->read_fd != -1)
		close(comline->read_fd);
	if (comline->write_fd != -1)
		close(comline->write_fd);
}

void	execute_command(t_list *list, t_vars *vars)
{
	pid_t		pid;
	t_comline	*order;

	order = (t_comline *)list->content;
	set_fd(list);
	// printf("read: %d, write: %d, next_read: %d\n", order->read_fd, order->write_fd, order->next_read_fd);
	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid == 0)
	{
		duplicate_output(order);
		close_fd_child(order);
		exec_ve(order->cmd, vars);
	}
	close_fd_parent(order);
}

void	execute_shell(t_list *list, t_vars *vars)
{
	t_list		*buf;
	t_comline	*order;

	buf = list;
	while (buf)
	{
		order = (t_comline *)buf->content;
		if (order->type == COMMAND)
			execute_command(buf, vars);
		else if (order->type == SHELL)
			;
		else if (order->type == PIPE)
			;
		else if (order->type == AND || order->type == OR)
			;
		else if (order->type == GTGT || order->type == GT
			|| order->type == LT || order->type == LTLT)
			execute_redirection(buf, vars);
		buf = buf->next;
	}
	int i = 0;
	while (i < 3)
	{
		wait(NULL);
		i++;
	}
}
