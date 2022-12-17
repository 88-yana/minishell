/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:57:37 by yahokari          #+#    #+#             */
/*   Updated: 2022/12/17 23:48:20 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include	"stdio.h"
# include	"stdbool.h"
# include	"../libft/libft.h"

int	g_status;

# define DOUBLEQ '"'
# define SINGLEQ '\''
# define BRA '('
# define CKET ')'

# define CNTARRLEN 0
# define CNTSTRLEN 1
# define PUSHELEM 2

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
	LT,
	GT,
	GTGT,
	LTLT,
	SUBSHELL,
	COMMAND,
	AND,
	OR
}	t_type;

typedef struct s_order {
	t_type	type;
	char	**cmd;
	size_t	pipe_num;
	bool	can_exec;
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	char	*file;
	t_list	*shell;
}	t_order;

typedef struct s_array
{
	char	*line;
	size_t	pos;
	size_t	*strs_len;
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
	char	*line;
	char	**array;
	t_list	*comline;
	t_list	*envs;
}	t_vars;

#endif
