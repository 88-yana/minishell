/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:51:50 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/31 17:45:27 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

void	interrupt_heredoc(int signal)
{
	(void)signal;
	printf("\n");
	exit(EXIT_SUCCESS);
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

void	get_heredoc(t_list *comline)
{
	t_order	*order;
	char	*end;
	int		fd;
	pid_t	pid;

	order = (t_order *)comline->content;
	if (!ft_strchr(order->file, SINGLEQ) && !ft_strchr(order->file, DOUBLEQ))
		order->is_quote = false;
	else
		order->is_quote = true;
	end = ft_strdup(order->file);
	if (!end)
		return ;
	delete_quote(end);
	make_tmp_file(order);
	fd = open(order->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		read_heredoc(end, fd);
	wait(NULL);
	close(fd);
	free(end);
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
			if (order->type == SUBSHELL)
				check_comline(order->shell);
		}
		else if (order->type == AND || order->type == OR)
			count = 0;
		else if (order->type == LTLT)
			get_heredoc(buf);
		buf = buf->next;
	}
}
