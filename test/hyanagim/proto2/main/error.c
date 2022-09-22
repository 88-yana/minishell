/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:32:43 by hyanagim          #+#    #+#             */
/*   Updated: 2022/09/22 15:29:21 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(const char *message)
{
	write(2, "Error\n", ft_strlen("Error\n"));
	write(2, message, ft_strlen(message));
	exit (1);
}
