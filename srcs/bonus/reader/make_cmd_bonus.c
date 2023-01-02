/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:48:35 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 19:07:26 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

char	**make_cmd(t_str *start, t_str *last, int cnt)
{
	t_str	*current;
	char	**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (cnt + 1));
	current = start;
	i = 0;
	while (i < cnt)
	{
		cmd[i] = current->str;
		if (current == last)
			break ;
		current = current->next;
		i++;
	}
	cmd[cnt] = NULL;
	return (cmd);
}

t_str	*make_slistcmd(char **cmd)
{
	t_str	*list;

	list = malloc(sizeof(t_str));
	if (list == NULL)
		return (NULL);
	list->type = COMMAND;
	list->str = NULL;
	list->cmd = cmd;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}
