/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:26:54 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/23 14:14:04 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_comline	*make_command(t_type type, char **cmd, char *file, t_list *shell)
{
	t_comline	*command_line;

	command_line = malloc(sizeof(t_comline));
	command_line->type = type;
	if (type == COMMAND)
		command_line->cmd = cmd;
	else
		command_line->cmd = NULL;
	if (type == GTGT || type == GT || type == LTLT || type == LT)
		command_line->file = file;
	else
		command_line->file = NULL;
	command_line->read_fd = -1;
	command_line->write_fd = -1;
	command_line->next_read_fd = -1;
	if (type == SHELL)
		command_line->shell = shell;
	else
		command_line->shell = NULL;
	return (command_line);
}

// size_t	count_pipes(t_list *shell)
// {
// 	size_t		count;
// 	t_list		*buf;
// 	t_comline	*command_line;

// 	count = 0;
// 	buf = shell;
// 	while (buf)
// 	{
// 		command_line = (t_comline *)buf->content;
// 		if (command_line->type == PIPE)
// 			count++;
// 		else if (command_line->type == AND || command_line->type == OR)
// 			break ;
// 		buf = buf->next;
// 	}
// 	return (count);
// }

// void	delete_command(void *content)
// {
// 	t_comline	*command_line;

// 	command_line = (t_comline *)command_line;
// 	free(command_line);
// }

void	display_command(t_list *command_line)
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

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	t_list	*command_line;

	(void)argc;
	(void)argv;
	vars.envp = envp;
	command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", "-l", NULL}, NULL, NULL));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/grep", "shell", NULL}, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(LT, NULL, "minishell.c", NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/wc", "-l", NULL}, NULL, NULL)));
	t_list	*sub = ft_lstnew(make_command(LT, NULL, "minishell.h", NULL));
	ft_lstadd_back(&sub, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/wc", "-l", NULL}, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(SHELL, NULL, NULL, sub)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/grep", "7", NULL}, NULL, NULL)));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/grep", "1", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/grep", "77", NULL}, NULL, NULL)));
	// display_command(command_line);
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/wc", "-l", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", NULL}, NULL, NULL)));

	// command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", "minishell.h", NULL}, NULL, NULL));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(GTGT, NULL, "test.txt", NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", NULL}, NULL, NULL)));

	// command_line = ft_lstnew(make_command(LT, NULL, "test.txt", NULL));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", "/dev/random", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/sleep", "5", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", NULL}, NULL, NULL)));
	// display_command(command_line);
	// command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", "-l", NULL}, NULL, NULL));
	execute_shell(command_line, &vars);
	// t_list	*next_command = find_last_commands(command_line);
	// next_command = find_last_commands(((t_comline *)next_command->content)->shell);
	// display_command(next_command);
	// t_comline *comline = next_command->content;
	// printf("read: %d, write: %d, next_read: %d\n", comline->read_fd, comline->write_fd, comline->next_read_fd);
	// find_last_commands(command_line);
}
