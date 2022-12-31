/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:17:33 by hyanagim          #+#    #+#             */
/*   Updated: 2022/12/30 21:17:35 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static void	print_list(t_str *current)
// {
// 	while (current != NULL)
// 	{
// 		if (current->type == STR)
// 			printf("str is 「%s」\n", current->str);
// 		else if (current->type == AIM)
// 			printf("aim is 「%s」\n", current->str);
// 		else if (current->type == CMD)
// 		{
// 			printf("%d\n", current->type);
// 			int i = 0;
// 			while (current->cmd[i] != NULL)
// 			{
// 				printf("cmd is %s\n", current->cmd[i]);
// 				i++;
// 			}
// 		}
// 		else
// 			printf("%d\n", current->type);
// 		current = current->next;
// 	}
// }

// static void	print_listr(t_str *current)
// {
// 	current = slistlast(current);
// 	while (current != NULL)
// 	{
// 		if (current->type == STR)
// 			printf("str is 「%s」\n", current->str);
// 		else if (current->type == AIM)
// 			printf("aim is 「%s」\n", current->str);
// 		else if (current->type == CMD)
// 		{
// 			printf("%d\n", current->type);
// 			int i = 0;
// 			while (current->cmd[i] != NULL)
// 			{
// 				printf("cmd is %s\n", current->cmd[i]);
// 				i++;
// 			}
// 		}
// 		else
// 			printf("%d\n", current->type);
// 		current = current->prev;
// 	}
// }