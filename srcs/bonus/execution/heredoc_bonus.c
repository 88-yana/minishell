/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:51:50 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/03 19:52:46 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution_bonus.h"

static void	interrupt_heredoc(int signal)
{
	(void)signal;
	printf("\n");
	exit(EXIT_FAILURE);
}

static char	*read_heredoc(char *end, int fd)
{
	char	*str;

	signal(SIGINT, interrupt_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, end))
			exit(EXIT_SUCCESS);
		ft_putendl_fd(str, fd);
		free(str);
	}
}

void	make_tmp_file(t_order *order)
{
	char	*file_name;
	char	*buf;

	file_name = ft_strdup(".tmpfile");
	while (!access(file_name, F_OK))
	{
		buf = ft_strjoin(file_name, "0");
		free(file_name);
		file_name = buf;
	}
	order->file = file_name;
}

static int	read_heredoc_with_status(t_order *order, char *end)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = open(order->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (fd == ERR || pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		read_heredoc(end, fd);
	wait(&status);
	close(fd);
	free(end);
	if (status == 256)
	{
		unlink(order->file);
		return (1);
	}
	return (0);
}

int	get_heredoc(t_list *comline)
{
	t_order	*order;
	char	*end;

	order = (t_order *)comline->content;
	if (!ft_strchr(order->file, SINGLEQ) && !ft_strchr(order->file, DOUBLEQ))
		order->is_quote = false;
	else
		order->is_quote = true;
	end = ft_strdup(order->file);
	free(order->file);
	if (!end)
		exit(EXIT_FAILURE);
	delete_quote(end);
	make_tmp_file(order);
	if (read_heredoc_with_status(order, end))
		return (1);
	return (0);
}
