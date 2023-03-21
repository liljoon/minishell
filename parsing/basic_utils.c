/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:17:41 by yham              #+#    #+#             */
/*   Updated: 2023/03/21 20:21:26 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}
