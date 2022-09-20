/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:04:06 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/20 19:43:10 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	display_command(t_list	*command_line)
{
	size_t		i;
	t_list		*buf;
	t_comline	*command;

	buf = command_line;
	while (buf)
	{
		command = (t_comline *)buf->content;
		if (command->type == COMMAND)
		{
			printf("type: [ %s ] command: [", "command");
			i = 0;
			while (command->cmd[i])
			{
				printf(" %s", command->cmd[i]);
				i++;
			}
			printf(" ]\n");
		}
		else if (command->type == SHELL)
		{
			printf("type: [ %s ]\n", "shell");
			printf("---------- inside shell ----------\n");
			display_command(command->shell);
		}
		else if (command->type == PIPE)
			printf("type: [ %s ]\n", "pipe");
		else if (command->type == AND)
			printf("type: [ %s ]\n", "and");
		else if (command->type == OR)
			printf("type: [ %s ]\n", "or");
		buf = buf->next;
	}
}

int	main(void)
{
	t_list	*command_line;

	command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", "-l", NULL}, NULL));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/echo", "$USER", NULL}, NULL)));
	display_command(command_line);
	printf("%ld\n", count_pipes(command_line));
	t_comline *com = (t_comline *)command_line->content;
	execute_shell(command_line);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	int	fd[2];
// 	int	fd1[2];
// 	if (pipe(fd) == -1)
// 		return 1;
// 	if (pipe(fd1) == -1)
// 		return 1;
// 	int pid1 = fork();
// 	if (pid1 < 0)
// 		return 2;
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[W], STDOUT_FILENO);
// 		close(fd[R]);
// 		close(fd[W]);
// 		close(fd1[R]);
// 		close(fd1[W]);
// 		execlp("cat", "cat", NULL);
// 	}
// 	int pid2 = fork();
// 	if (pid2 < 0)
// 		return 3;
// 	if (pid2 == 0)
// 	{
// 		dup2(fd[R], STDIN_FILENO);
// 		dup2(fd1[W], STDOUT_FILENO);
// 		close(fd[R]);
// 		close(fd[W]);
// 		close(fd1[R]);
// 		close(fd1[W]);
// 		execlp("cat", "cat", NULL);
// 	}
// 	int pid3 = fork();
// 	if (pid3 < 0)
// 		return 3;
// 	if (pid3 == 0)
// 	{
// 		dup2(fd1[R], STDIN_FILENO);
// 		close(fd[R]);
// 		close(fd[W]);
// 		close(fd1[R]);
// 		close(fd1[W]);
// 		execlp("ls", "ls", NULL);
// 	}
// 	close(fd[R]);
// 	close(fd[W]);
// 	close(fd1[R]);
// 	close(fd1[W]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return 0;
// }