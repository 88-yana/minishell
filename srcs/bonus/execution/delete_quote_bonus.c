/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:36:18 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/01 14:42:37 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

void	delete_quote(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOUBLEQ || str[i] == SINGLEQ)
		{
			quote = str[i];
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != quote)
				i++;
			if (str[i] == '\0')
				return ;
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		i++;
	}
}
