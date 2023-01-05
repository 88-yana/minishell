/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:00:08 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/05 16:11:08 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

static void	sigint_comline(int signal)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	(void)signal;
}

static void	sigquit_comline(int signal)
{
	(void)signal;
	ft_putendl_fd("Quit: 3", STDOUT_FILENO);
}

void	setup_signal_comline(void)
{
	signal(SIGINT, sigint_comline);
	signal(SIGQUIT, sigquit_comline);
}
