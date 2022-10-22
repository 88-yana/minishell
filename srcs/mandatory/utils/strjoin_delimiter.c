/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_delimiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:28 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/22 19:24:21 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/utils.h"

char	*strjoin_delimiter(char *s1, char *s2, char *delimiter)
{
	char	*buf;
	char	*str;

	buf = ft_strjoin(s1, delimiter);
	if (!buf)
		return (NULL);
	str = ft_strjoin(buf, s2);
	free(buf);
	if (!str)
		return (NULL);
	return (str);
}
