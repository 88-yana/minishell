/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:02:17 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/29 20:16:53 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"

void	exec_piped_commands(t_vars *vars, t_list *comline, t_list **pids)
{
	t_order	*order;

	order = (t_order *)comline->content;
	set_fd(comline);
	if (is_builtin(order->cmd) && order->pipe_num == 0
		&& !is_next_type(comline, PIPE))
		exec_pwd(vars);
	else
		exec_command_child(vars, comline, pids);
	close_fd_parent(order);
}

void	exec_redirection(t_list *comline)
{
	t_order	*order;

	order = (t_order *)comline->content;
	if (order->type == GTGT)
		exec_gtgt(comline);
	else if (order->type == GT)
		exec_gt(comline);
	else if (order->type == LTLT)
		exec_ltlt(comline);
	else if (order->type == LT)
		exec_lt(comline);
}

t_list	*exec_delimiters(t_list *comline, t_list **pids)
{
	t_order	*order;
	t_list	*next_delimiters;

	wait_pids(pids);
	order = (t_order *)comline->content;
	if ((order->type == AND && g_status == 0)
		|| (order->type == OR && g_status != 0))
		;
	else
	{
		next_delimiters = find_next_delimiters(comline);
		while (comline->next != next_delimiters)
			comline = comline->next;
	}
	return (comline);
}

void	exec_comline(t_vars *vars, t_list *comline)
{
	t_list	*pids;
	t_order	*order;

	pids = NULL;
	while (comline)
	{
		order = (t_order *)comline->content;
		if (order->type == COMMAND || order->type == SUBSHELL)
			exec_piped_commands(vars, comline, &pids);
		else if (order->type == PIPE)
			;
		else if (order->type == AND || order->type == OR)
			comline = exec_delimiters(comline, &pids);
		else if (order->type == GTGT || order->type == GT
			|| order->type == LT || order->type == LTLT)
			exec_redirection(comline);
		comline = comline->next;
	}
	wait_pids(&pids);
}
