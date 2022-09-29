/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:28 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 17:46:33 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../include/utils.h"

char	*strjoin_delimiter(char *s1, char *s2, char *delimiter)
{
	char	*buf;
	char	str;

	buf = ft_strjoin(s1, delimiter);
	if (!buf)
		return (NULL);
	str = ft_strjoin(buf, s2);
	if (!str)
		return (NULL);
	free(buf);
	return (str);
}
