/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:34:39 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/23 21:16:27 by yahokari         ###   ########.fr       */
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
	// if (WIFSIGNALED(status) == TRUE)
	// 	g_status = 128 + WTERMSIG(status);
	// else
	// 	g_status = WEXITSTATUS(status);
	pid = NULL; //need modified
}

// int	main(void)
// {
// 	t_list	*list;

// 	list = NULL;
// 	create_pid_list(&list, 100);
// 	create_pid_list(&list, 200);
// 	while (list)
// 	{
// 		printf("%d\n", (*(pid_t *)list->content));
// 		list = list->next;
// 	}
// 	return (0);
// }
