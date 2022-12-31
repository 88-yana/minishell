/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_free_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:10:10 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:47:19 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

void	safe_free_double_char(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
