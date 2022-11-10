/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   talloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:13:13 by hyanagim          #+#    #+#             */
/*   Updated: 2022/11/10 21:14:59 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../../includes/parser.h"

t_node	*talloc(t_type type, t_node *parent)
{
	t_node	*p;

	p = malloc(sizeof(t_node));
	p->type = type;
	p->detail = parent->detail;
	p->line = parent->line;
	p->ele_is_quoted = parent->ele_is_quoted;
	p->ele_length = parent->ele_length;
	p->array_size = parent->array_size;
	p->start_pos = parent->start_pos;
	p->current_pos = parent->current_pos;
	p->end_pos = parent->end_pos;
	p->include_right = parent->include_right;
	p->index = parent->index + 1;
	p->parent = parent;
	p->left = parent->left;
	p->right = parent->right;
	return (p);
}
//talloc 失敗した時のエラー処理を後で書く