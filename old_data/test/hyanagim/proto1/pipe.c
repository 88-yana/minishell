/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:04:06 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/19 18:03:09 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define R 0
#define W 1

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	fd1[2];
	if (pipe(fd) == -1)
		return 1;
	if (pipe(fd1) == -1)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		dup2(fd[W], STDOUT_FILENO);
		close(fd[R]);
		close(fd[W]);
		close(fd1[R]);
		close(fd1[W]);
		execlp("cat", "cat", NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		dup2(fd[R], STDIN_FILENO);
		dup2(fd1[W], STDOUT_FILENO);
		close(fd[R]);
		close(fd[W]);
		close(fd1[R]);
		close(fd1[W]);
		execlp("ls", "ls", NULL);
	}
	int pid3 = fork();
	if (pid3 < 0)
		return 3;
	if (pid3 == 0)
	{
		dup2(fd1[R], STDIN_FILENO);
		close(fd[R]);
		close(fd[W]);
		close(fd1[R]);
		close(fd1[W]);
		execlp("cat", "cat", NULL);
	}
	close(fd[R]);
	close(fd[W]);
	close(fd1[R]);
	close(fd1[W]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}