/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:54:41 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 22:57:26 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

void	traverse_command(t_node *p, t_list ***list)
{
	char	**array;
	size_t	i;
	t_list	*list_ptr;

	while (p->line[p->end_pos] != NULL && !is_delimiter(p->line[p->end_pos])
		&& !is_bra(p->line[p->end_pos]) && !is_pipe(p->line[p->end_pos])
		&& !is_redirection(p->line[p->end_pos]))
		p->end_pos++;
	array = malloc(sizeof(char *) * (p->end_pos - p->start_pos + 1));
	if (array == NULL)
		; //後で書く。
	i = 0;
	while (i < p->end_pos - p->start_pos)
	{
		array[i] = ft_strdup(p->line[p->start_pos + i]);
		if (array[i] == NULL)
			; //後で書く。
		i++;
	}
	array[i] = NULL;
	list_ptr = ft_lstnew(make_command(COMMAND, array, NULL, NULL));
	*list = realloc_list(*list, list_ptr);
}
