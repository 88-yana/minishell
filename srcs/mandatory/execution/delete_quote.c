/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:36:18 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/31 18:31:44 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	del(char *str, char quote, size_t i)
{
	ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
	while (str[i] != '\0' && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return ;
	ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
}

void	delete_quote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOUBLEQ || str[i] == SINGLEQ)
		{
			del(str, str[i], i);
			continue ;
		}
		i++;
	}
}
