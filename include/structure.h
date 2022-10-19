/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:57:37 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/19 15:19:40 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include	"stdio.h"
# include	"stdbool.h"
# include	"../libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef enum e_type {
	COMMAND_LINE,
	PIPED_LINE,
	PIPE,
	DELIMITER,
	ARGUMENTS,
	REDIRECTION,
	STRING,
	EXPANDABLE,
	NOT_EXPANDABLE,
	EXPANDABLE_QUOTED,
	SUBSHELL,
	LT,
	GT,
	GTGT,
	LTLT,
	COMMAND,
	AND,
	OR
}	t_type;

typedef struct s_order {
	t_type	type;
	char	**cmd;
	size_t	pipe_num;
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	char	*file;
	t_list	*shell;
}	t_order;

typedef struct s_split
{
	char	*line;
	size_t	pos;
	size_t	size;
	size_t	*length;
	char	**array;
}	t_array;

typedef struct s_node
{
	t_type			type;
	t_type			detail;
	char			**line;
	int				*ele_is_quoted;
	size_t			*ele_length;
	size_t			array_size;
	size_t			start_pos;
	size_t			current_pos;
	size_t			end_pos;
	bool			include_right;
	size_t			index;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_envs {
	char	*type;
	char	*value;
}	t_envs;

typedef struct s_vars {
	t_list	*comline;
	t_list	*pids;
	t_list	*envs;
}	t_vars;

extern int g_status;

#endif
