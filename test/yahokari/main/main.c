/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:10:22 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 20:04:25 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"main.h"

t_order	*make_command(t_type type, char **cmd, char *file, t_list *shell)
{
	t_order	*command_line;

	command_line = malloc(sizeof(t_order));
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
	if (type == SUBSHELL)
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
	size_t	i;
	t_list	*buf;
	t_order	*command;

	buf = command_line;
	while (buf)
	{
		command = (t_order *)buf->content;
		printf("type is %d\n", command->type);
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
		else if (command->type == SUBSHELL)
		{
			printf("type: [ %s ]\n", "shell");
			printf("---------- inside shell ----------\n");
			display_command(command->shell);
		}
		else if (command->type == GT)
		{
			printf("type: [ %s ]", "gt");
			printf("aim: %s", command->file);
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
	char	*str;

	(void)argc;
	(void)argv;

	vars.envs_list = NULL;
	convert_envp_to_list(&vars, envp);
	// command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", "-l", NULL}, NULL, NULL));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/grep", "pi", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(LT, NULL, "pid.c", NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/wc", "-l", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// t_list	*sub = ft_lstnew(make_command(LT, NULL, "redirection.c", NULL));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(COMMAND, (char *[]){"/usr/bin/wc", "-l", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(SUBSHELL, NULL, NULL, sub)));

	// t_list	*sub = ft_lstnew(make_command(COMMAND, (char *[]){"cat", NULL}, NULL, NULL));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(COMMAND, (char *[]){"ls", NULL}, NULL, NULL)));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&sub, ft_lstnew(make_command(COMMAND, (char *[]){"ls", NULL}, NULL, NULL)));
	// command_line = ft_lstnew(make_command(SUBSHELL, NULL, NULL, sub));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(AND, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"wc", "-l", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"cat", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"ls", NULL}, NULL, NULL)));

	command_line = ft_lstnew(make_command(COMMAND, (char *[]){"ls", "-l", NULL}, NULL, NULL));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(AND, NULL, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"ls", "-4", NULL}, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(OR, NULL, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"cat", NULL}, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"ls", NULL}, NULL, NULL)));

	// command_line = ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", NULL}, NULL, NULL));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/cat", NULL}, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(PIPE, NULL, NULL, NULL)));
	// ft_lstadd_back(&command_line, ft_lstnew(make_command(COMMAND, (char *[]){"/bin/ls", NULL}, NULL, NULL)));
	while (true)
	{
		str = exec_readline();
		exec_comline(&vars, command_line);
		free(str);
	}
}
