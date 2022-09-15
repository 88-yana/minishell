/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahokari <yahokari@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:03:51 by yahokari          #+#    #+#             */
/*   Updated: 2022/09/15 21:09:56 by yahokari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parser.h"

t_tree	*talloc(t_symbol symbol)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		exit(1);
	tree->type = symbol;
	return (tree);
}
