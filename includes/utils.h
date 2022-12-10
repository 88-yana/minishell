/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:42:40 by yahokari          #+#    #+#             */
/*   Updated: 2022/11/19 21:14:29 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include	"../libft/libft.h"
# include	"define.h"

char	*strjoin_delimiter(char *s1, char *s2, char *delimiter);
size_t	count_lstsize(t_list *lst);
char	*substr_size_t(char const *s, size_t start, size_t len);
void	safe_free_double_char(char **str);
void	go_advance(size_t *i, size_t *str_len);
size_t	arraylen(char **array);
char	**arrayjoin(char **arr1, char**arr2);
void	free_doubleptr(char **array);

#endif
