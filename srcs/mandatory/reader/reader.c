/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:08:14 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/07 22:14:40 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	init_new_lexer(int *i, int *str_len, bool during_[2], t_str **line)
{
	*i = -1;
	*str_len = -1;
	during_[DQ] = false;
	during_[SQ] = false;
	*line = NULL;
}

static t_str	*new_lexer(char *line)
{
	int		i;
	int		str_len;
	bool	during_[2];
	t_str	*lexical_line;

	init_new_lexer(&i, &str_len, during_, &lexical_line);
	while (1)
	{
		i++;
		str_len++;
		if (line[i] == DOUBLEQ)
			during_[DQ] = !during_[DQ];
		if (line[i] == SINGLEQ)
			during_[SQ] = !during_[SQ];
		if (during_[DQ] || during_[SQ])
			continue ;
		if (is_se(line[i]))
			cutline(&lexical_line, line, &i, &str_len);
		if (line[i] == '\0')
			break ;
	}
	return (lexical_line);
}

static t_list	*free_all(char *line, t_str *lexical)
{
	printf("syntax error near unexpected token\n");
	free(line);
	free_slistall(lexical);
	return (NULL);
}

static t_list	*free_line_list(char *line, t_list *list)
{
	free(line);
	free_list(list);
	return (NULL);
}

void	display_command(t_list *command_line)
{
	size_t	i;
	t_list	*buf;
	t_order	*command;

	buf = command_line;
	while (buf)
	{
		command = (t_order *)buf->content;
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
			printf("---------- inside shell ----------\n");
			printf("type: [ %s ]\n", "shell");
			display_command(command->shell);
			printf("---------- inside shell ----------\n");
		}
		else if (command->type == GT)
		{
			printf("type: [ %s ]", "gt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == LT)
		{
			printf("type: [ %s ]", "lt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == GTGT)
		{
			printf("type: [ %s ]", "gtgt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == LTLT)
		{
			printf("type: [ %s ]", "ltlt");
			printf(" aim: [ %s ]\n", command->file);
		}
		else if (command->type == PIPE)
			printf("type: [ %s ]\n", "pipe");
		else if (command->type == AND)
			printf("type: [ %s ]\n", "and");
		else if (command->type == OR)
			printf("type: [ %s ]\n", "or");
		else if (command->type == BRA)
			printf("type: [ %s ]\n", "bra");
		else if (command->type == CKET)
			printf("type: [ %s ]\n", "cket");
		buf = buf->next;
	}
}

t_list	*reader(char *line)
{
	t_str	*lexical_line;
	t_list	*list;

	if (check_line(line) == false)
		return (free_line(line));
	lexical_line = new_lexer(line);
	if (lexical_line == NULL)
		return (free_line(line));
	if (check_lex(lexical_line) == false)
		return (free_all(line, lexical_line));
	if (!str_to_aim(lexical_line))
		return (free_all(line, lexical_line));
	sort_red_str(lexical_line);
	str_to_cmd(&lexical_line);
	list = str_to_list(lexical_line);
	sort_red_cmd(list);
	free_slist(lexical_line);
	list_to_subshell(&list);
	if (!sort_shell_cmd(list))
		return (free_line_list(line, list));
	free(line);
	return (list);
}
