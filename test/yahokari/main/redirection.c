/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:19:14 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/22 17:40:49 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	execute_lt(t_list *list)
{
	int			fd;
	t_comline	*comline;
	t_comline	*next_comline;
	t_list		*next_command;

	comline = (t_comline *)list->content;
	fd = open(comline->file, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	next_command = find_next_piped_commands(list);
	next_comline = (t_comline *)next_command->content;
	if (next_comline->read_fd != -1)
		close(next_comline->read_fd);
	next_comline->read_fd = fd;
}

void	execute_gt(t_list *list)
{
	int			fd;
	t_comline	*comline;
	t_comline	*next_comline;
	t_list		*next_command;

	comline = (t_comline *)list->content;
	fd = open(comline->file, O_WRONLY | O_CREAT | 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	next_command = find_next_piped_commands(list);
	next_comline = (t_comline *)next_command->content;
	if (next_comline->write_fd != -1)
		close(next_comline->write_fd);
	next_comline->write_fd = fd;
}

void	execute_gtgt(t_list *list)
{
	int			fd;
	t_comline	*comline;
	t_comline	*next_comline;
	t_list		*next_command;

	comline = (t_comline *)list->content;
	fd = open(comline->file, O_WRONLY | O_CREAT | O_APPEND | 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	next_command = find_next_piped_commands(list);
	next_comline = (t_comline *)next_command->content;
	if (next_comline->write_fd != -1)
		close(next_comline->write_fd);
	next_comline->write_fd = fd;
}

void	execute_redirection(t_list *list, t_vars *vars)
{
	t_comline	*order;

	order = (t_comline *)list->content;
	if (order->type == GTGT)
		execute_gtgt(list);
	else if (order->type == GT)
		execute_gt(list);
	else if (order->type == LTLT)
		;
	else if (order->type == LT)
		execute_lt(list);
}
