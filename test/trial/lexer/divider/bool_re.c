/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_re.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:11:40 by hyanagim          #+#    #+#             */
/*   Updated: 2022/10/03 17:55:23 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "divide_quote.h"

bool	is_separator_div(char c)
{
	if (c == '\0')
		return (true);
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	if (c == '(')
		return (true);
	if (c == ')')
		return (false);
}
