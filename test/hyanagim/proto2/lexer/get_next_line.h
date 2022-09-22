/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:36:48 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/22 18:58:48 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define FILE_OPEN_MAX 255

size_t	gt_strlen(const char *str);
char	*gt_strlcpy(char **save, size_t start, size_t n);
char	*gt_free(char **save, char **buf);
int		gt_find_nl(char *s);
char	*get_line(int fd);
#endif