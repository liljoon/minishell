/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:28:39 by yham              #+#    #+#             */
/*   Updated: 2023/03/16 21:23:41 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_and_free_sub(char *str, int start, int len)
{
	int		args_in_str;
	char	*sub;

	sub = ft_substr(str, start, len);
	args_in_str = count_arg_in_str(sub);
	free(sub);
	return (args_in_str);
}
