/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:39:46 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/02 17:22:42 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../../../libft/libft.h"
# include	"../main/main.h"
# include	"../command_line/comline.h"

typedef struct s_envs {
	char	*type;
	char	*value;
}	t_envs;

char	**get_envp_from_list(t_list *list);
void	convert_envp_to_list(t_vars *vars, char **envp);
void	create_envs_list(t_list **list, char *str);
char	*find_env(t_list *list, char *to_find);

#endif