/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:31:54 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 16:33:36 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_bonus.h"

static t_list	*find_bra(t_list *head)
{
	t_list	*current;

	current = ft_lstlast(head);
	while (((t_order *)current->content)->type != BRA && current->prev != NULL)
		current = current->prev;
	return (current);
}

static t_list	*find_cket(t_list *current)
{
	while (((t_order *)current->content)->type != CKET)
		current = current->next;
	return (current);
}

static bool	conv_list_to_subshell(t_list **list)
{
	t_list	*bra;
	t_list	*cket;
	t_list	*current;

	bra = find_bra(*list);
	if (((t_order *)bra->content)->type != BRA)
		return (false);
	current = bra;
	cket = find_cket(current);
	bra->next->prev = NULL;
	cket->prev->next = NULL;
	((t_order *)bra->content)->type = SUBSHELL;
	((t_order *)bra->content)->shell = bra->next;
	bra->next = cket->next;
	if (cket->next)
		cket->next->prev = bra;
	free(cket->content);
	free(cket);
	return (true);
}

void	list_to_subshell(t_list **list)
{
	while (1)
	{
		if (conv_list_to_subshell(list) == false)
			break ;
	}
}
