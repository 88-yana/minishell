/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:36:46 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/20 17:15:51 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_comline	*make_command(t_type type, char **cmd, t_list *shell)
{
	t_comline	*command_line;

	command_line = malloc(sizeof(t_comline));
	command_line->type = type;
	command_line->cmd = cmd;
	command_line->shell = shell;
	return (command_line);
}

size_t	count_pipes(t_list *shell)
{
	size_t		count;
	t_list		*buf;
	t_comline	*command_line;

	count = 0;
	buf = shell;
	while (buf)
	{
		command_line = (t_comline *)buf->content;
		if (command_line->type == PIPE)
			count++;
		else if (command_line->type == AND || command_line->type == OR)
			break ;
		buf = buf->next;
	}
	return (count);
}

void	delete_command(void *content)
{
	t_comline	*command_line;

	command_line = (t_comline *)command_line;
	free(command_line);
}
