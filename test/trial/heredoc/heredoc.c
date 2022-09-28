/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:51:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/28 20:10:45 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"heredoc.h"

void	exit_heredoc(void)
{
	exit(0);
}

void	interrupt_heredoc(int signal)
{
	(void)signal;
	exit(1);
}

char	*read_heredoc(char *end, int fd)
{
	char	*str;

	while (true)
	{
		signal(SIGINT, interrupt_heredoc);
		signal(SIGQUIT, SIG_IGN);
		str = readline("> ");
		if (!str || !ft_strcmp(str, end))
			exit_heredoc();
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

void	get_heredoc(t_list *comline)
{
	t_order	*order;
	char	*end;
	int		fd;
	pid_t	pid;

	order = (t_order *)comline->content;
	end = order->file;
	make_tmp_file(order);
	fd = open(order->file, O_WRONLY | O_CREAT);
	pid = fork();
	if (pid < 0)
		exit (1);
	else if (pid == 0)
		read_heredoc(end, fd);
	printf("hello");
	wait(NULL);
	close(fd);
}

void	check_comline(t_list *comline)
{
	t_list	*buf;
	size_t	count;
	t_order	*order;

	count = 0;
	buf = comline;
	while (buf)
	{
		order = (t_order *)buf->content;
		if (order->type == COMMAND || order->type == SUBSHELL)
		{
			order->pipe_num = count;
			count++;
		}
		else if (order->type == AND || order->type == OR)
			count = 0;
		else if (order->type == LTLT)
			get_heredoc(buf);
		buf = buf->next;
	}
}
