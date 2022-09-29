/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:51:13 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 17:51:52 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/utils.h"

size_t	count_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (!lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
