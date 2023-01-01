/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:57:37 by yahokari          #+#    #+#             */
/*   Updated: 2023/01/01 14:55:09 by hyanagim         ###   ########.fr       */
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

# define DQ 0
# define SQ 1

# define CNTARRLEN 0
# define CNTSTRLEN 1
# define PUSHELEM 2

# define ERR -1
# define NONE -1

# define READ 0
# define WRITE 1

# define CHILD 0

# define CWD 0
# define ASTERISK 1

typedef enum e_type {
	PIPE,
	LT,
	GT,
	GTGT,
	LTLT,
	SUBSHELL,
	COMMAND,
	AND,
	OR,
	STR,
	AIM,
	BRA,
	CKET
}	t_type;

typedef struct s_str
{
	t_type			type;
	char			*str;
	char			**cmd;
	struct s_str	*next;
	struct s_str	*prev;
}	t_str;

typedef struct s_order {
	t_type	type;
	char	**cmd;
	size_t	pipe_num;
	bool	is_quote;
	bool	can_exec;
	int		read_fd;
	int		write_fd;
	int		next_read_fd;
	char	*file;
	t_list	*shell;
}	t_order;

typedef struct s_envs {
	char	*type;
	char	*value;
}	t_envs;

typedef struct s_vars {
	char	*line;
	t_list	*comline;
	t_list	*envs;
}	t_vars;

#endif
