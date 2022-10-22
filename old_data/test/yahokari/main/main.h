/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:44:40 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/27 19:35:38 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include	"../../../libft/libft.h"

typedef struct s_vars {
	t_list	*comline;
	t_list	*pids;
	t_list	*envs_list;
}	t_vars;

# include	"../command_line/comline.h"
# include	"../readline/readline.h"
# include	"../env/env.h"
# include	"../heredoc/heredoc.h"
# include	"../builtin/builtin.h"

#endif
