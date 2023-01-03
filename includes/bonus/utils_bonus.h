/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:40 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/03 09:24:26 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include	"../../libft/libft.h"
# include	"define.h"

char	*strjoin_delimiter(char *s1, char *s2, char *delimiter);
size_t	count_lstsize(t_list *lst);
char	*substr_size_t(char const *s, size_t start, size_t len);
void	safe_free_double_char(char **str);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
void	free_doubleptr(char **array);

#endif
