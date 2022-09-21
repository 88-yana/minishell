/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:09:24 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/20 21:47:17 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	execute_command(char **command)
{
	execve(command[0], command, NULL);
	// execlp(command[0], command[0], NULL);
}

void	initialize_pipe(t_pipe_fd *pipe_fd)
{
	int	buf[2];

	pipe(buf);
	pipe_fd->read_fd = -1;
	pipe_fd->next_read_fd = buf[0];
	pipe_fd->write_fd = buf[1];
}

void	execute_initial_pipe(char **command, t_pipe_fd *pipe_fd)
{
	pid_t	pid;

	initialize_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid == 0)
	{
		dup2(pipe_fd->write_fd, STDOUT_FILENO);
		close(pipe_fd->write_fd);
		close(pipe_fd->next_read_fd);
		execute_command(command);
	}
	close(pipe_fd->write_fd);
}

void	update_pipe(t_pipe_fd *pipe_fd)
{
	int	buf[2];

	pipe(buf);
	pipe_fd->read_fd = pipe_fd->next_read_fd;
	pipe_fd->next_read_fd = buf[0];
	pipe_fd->write_fd = buf[1];
}

void	execute_pipe(char **command, t_pipe_fd *pipe_fd)
{
	pid_t	pid;

	update_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid == 0)
	{
		dup2(pipe_fd->read_fd, STDIN_FILENO);
		dup2(pipe_fd->write_fd, STDOUT_FILENO);
		close(pipe_fd->read_fd);
		close(pipe_fd->write_fd);
		close(pipe_fd->next_read_fd);
		execute_command(command);
	}
	close(pipe_fd->read_fd);
	close(pipe_fd->write_fd);
}

void	last_pipe(t_pipe_fd *pipe_fd)
{
	pipe_fd->read_fd = pipe_fd->next_read_fd;
	pipe_fd->next_read_fd = -1;
	pipe_fd->write_fd = -1;
}

void	execute_last_pipe(char **command, t_pipe_fd *pipe_fd)
{
	pid_t	pid;

	last_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid == 0)
	{
		dup2(pipe_fd->read_fd, STDIN_FILENO);
		close(pipe_fd->read_fd);
		execute_command(command);
	}
	close(pipe_fd->read_fd);
}

void	execute_piped_command(t_list *list)
{
	size_t		i;
	size_t		pipes;
	t_list		*buf;
	t_comline	*command;
	t_pipe_fd	pipe_fd;

	i = 0;
	buf = list;
	pipes = count_pipes(buf);
	while (i <= pipes)
	{
		command = (t_comline *)buf->content;
		if (command->type == PIPE)
		{
			buf = buf->next;
			continue ;
		}
		if (i == 0)
			execute_initial_pipe(command->cmd, &pipe_fd);
		else if (i == pipes)
			execute_last_pipe(command->cmd, &pipe_fd);
		else
			execute_pipe(command->cmd, &pipe_fd);
		i++;
		buf = buf->next;
	}
}	

void	execute_shell(t_list *list)
{
	t_list		*buf;
	t_comline	*command;
	size_t		pipes;
	size_t		i;

	buf = list;
	pipes = count_pipes(buf);
	command = buf->content;
	if (pipes == 0 && command->type == COMMAND)
		execute_command(command->cmd);
	else
		execute_piped_command(buf);
	i = 0;
	while (i <= pipes)
	{
		wait(NULL);
		i++;
	}
	// while (buf)
	// {
	// 	pipes = count_pipes(buf);
	// 	command = buf->content;
	// 	// printf("%ld\n", count_pipes(buf));
	// 	// display_command(buf);
	// 	if (pipes == 0 && command->type == COMMAND)
	// 		execute_command(command->cmd);
	// 	buf = buf->next;
	// }
}
