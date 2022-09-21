/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:04:06 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/21 17:45:59 by yahokari         ###   ########.fr       */
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

	// command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", "-l", NULL}, NULL));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/grep", "main", NULL}, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/wc", "-l", NULL}, NULL)));
	command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", "Makefile", "shell.c", NULL}, NULL));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", NULL}, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", NULL}, NULL)));
	// display_command(command_line);
	// printf("%ld\n", count_pipes(command_line));
	// t_comline *com = (t_comline *)command_line->content;
	execute_shell(command_line);
	return (0);
}
