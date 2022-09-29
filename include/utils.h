/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:40 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 18:11:08 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include	"../libft/libft.h"

char	*strjoin_delimiter(char *s1, char *s2, char *delimiter);
size_t	count_lstsize(t_list *lst);
char	*substr_size_t(char const *s, size_t start, size_t len);

#endif
