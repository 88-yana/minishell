/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:56:03 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 22:59:54 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include	"structure.h"
# include	"execution.h"
# include	<fcntl.h>

void	exec_lt(t_list *comline);
void	exec_ltlt(t_list *comline);
void	exec_gt(t_list *comline);
void	exec_gtgt(t_list *comline);

#endif
