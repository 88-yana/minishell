/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:36:03 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:03:29 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static t_str	*find_startstr(t_str *head)
{
	while (head->type != STR && head->next != NULL)
		head = head->next;
	return (head);
}

static t_str	*find_laststr(t_str *head, int *cnt)
{
	while (head->next != NULL && head->next->type == STR)
	{
		head = head->next;
		(*cnt)++;
	}
	return (head);
}

static void	free_sliststr(t_str *start, t_str *last)
{
	t_str	*temp;
	t_str	*current;

	current = start;
	while (1)
	{
		temp = current->next;
		free(current);
		if (current == last)
			break ;
		current = temp;
	}
}

static void	connect_cmd(t_str **head, t_str *start, t_str *last, t_str *cmdlist)
{
	if (start->prev)
	{
		start->prev->next = cmdlist;
		cmdlist->prev = start->prev;
		cmdlist->next = last->next;
	}
	else
	{
		*head = cmdlist;
		cmdlist->next = last->next;
	}
	if (last->next)
	{
		last->next->prev = cmdlist;
		cmdlist->prev = start->prev;
		cmdlist->next = last->next;
	}
	free_sliststr(start, last);
}

static bool	conv_str_to_cmd(t_str **head)
{
	t_str	*start;
	t_str	*last;
	t_str	*current;
	t_str	*cmdlist;
	int		cnt;

	start = find_startstr(*head);
	if (start->type != STR)
		return (false);
	current = start;
	cnt = 1;
	last = find_laststr(current, &cnt);
	cmdlist = make_slistcmd(make_cmd(start, last, cnt));
	connect_cmd(head, start, last, cmdlist);
	return (true);
}

void	str_to_cmd(t_str **lexical_line)
{
	while (1)
	{
		if (conv_str_to_cmd(lexical_line) == false)
			break ;
	}
}
