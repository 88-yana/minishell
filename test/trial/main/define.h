/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:18:11 by yahokari          #+#    #+#             */
/*   Updated: 2022/10/06 21:23:12 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEFINE_H
# define DEFINE_H

# include	"../../../libft/libft.h"
# include	<stddef.h>
# include	<fcntl.h>
# include	<stdbool.h>

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
	size_t	quote[2];
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

typedef struct s_vars {
	t_list	*comline;
	t_list	*pids;
	t_list	*envs_list;
}	t_vars;

#endif
