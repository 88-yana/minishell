/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:40:37 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:44:07 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

static void	chenage_file_with_env(t_vars *vars, int fd_from, int fd_to)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd_from);
		if (!line)
			break ;
		line = lexer_envs(vars, line);
		ft_putstr_fd(line, fd_to);
		free(line);
	}
}

void	change_file(t_vars *vars, t_list *comline)
{
	int		fd_from;
	int		fd_to;
	char	*tmp;
	t_order	*order;

	order = (t_order *)comline->content;
	fd_from = open(order->file, O_RDONLY);
	if (fd_from == ERR)
		exit (EXIT_FAILURE);
	tmp = order->file;
	make_tmp_file(order);
	fd_to = open(order->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_to == ERR)
		exit (EXIT_FAILURE);
	chenage_file_with_env(vars, fd_from, fd_to);
	close(fd_from);
	close(fd_to);
	unlink(tmp);
	free(tmp);
}
