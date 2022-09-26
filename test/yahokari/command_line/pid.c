/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:34:39 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/24 18:10:46 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"comline.h"

void	create_pid_list(t_list **list, pid_t pid)
{
	pid_t	*buf;

	buf = malloc(sizeof(pid_t));
	if (!buf)
		return ;
	*buf = pid;
	if (list == NULL)
		*list = ft_lstnew(buf);
	else
		ft_lstadd_back(list, ft_lstnew(buf));
}

void	wait_pids(t_list **pids)
{
	t_list	*buf;
	int		status;
	int		*pid;

	buf = *pids;
	if (buf == NULL)
		return ;
	while (buf)
	{
		pid = (pid_t *)(buf->content);
		waitpid(*pid, &status, 0);
		buf = buf->next;
	}
	if (WIFSIGNALED(status) == TRUE)
		g_status = 128 + WTERMSIG(status);
	else
		g_status = WEXITSTATUS(status);
	*pids = NULL; //need modified
}
