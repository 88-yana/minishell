/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:36:18 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/18 15:40:19 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	delete_quote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOUBLEQ)
		{
			free(str[i]);
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != DOUBLEQ)
				i++;
			if (str[i] == '\0')
				break ;
			free(str[i]);
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		if (str[i] == SINGLEQ)
		{
			free(str[i]);
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			while (str[i] != '\0' && str[i] != SINGLEQ)
				i++;
			if (str[i] == '\0')
				break ;
			free(str[i]);
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
			continue ;
		}
		i++;
	}
}
