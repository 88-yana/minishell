/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:08:41 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 17:00:51 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"

static void	free_doublechar(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_list(t_list *head)
{
	t_list	*temp;
	t_list	*current;

	current = head;
	while (1)
	{
		temp = current->next;
		if (((t_order *)current->content)->type == COMMAND)
			free_doublechar(((t_order *)current->content)->cmd);
		if (is_redirect(((t_order *)current->content)->type))
			free(((t_order *)current->content)->file);
		if (((t_order *)current->content)->type == SUBSHELL)
			free_list(((t_order *)current->content)->shell);
		free(current->content);
		free(current);
		current = temp;
		if (current == NULL)
			break ;
	}
}
