/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:40:37 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/05 18:18:12 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution_bonus.h"

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

int	check_file_and_open(t_vars *vars, t_order *order)
{
	int	fd;

	order->file = lexer_envs(vars, order->file);
	delete_quote(order->file);
	fd = open(order->file, O_RDONLY);
	if (fd == ERR)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(order->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_status = 1;
	}
	return (fd);
}

int	check_file_and_open_gt_gtgt(t_vars *vars, t_order *order)
{
	int	fd;

	order->file = lexer_envs(vars, order->file);
	delete_quote(order->file);
	fd = open(order->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == ERR)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(order->file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_status = 1;
	}
	return (fd);
}
