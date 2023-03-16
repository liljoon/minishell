/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:19:52 by yham              #+#    #+#             */
/*   Updated: 2023/03/16 21:21:33 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_argv(t_argv *argv, char *command)
{
	argv->data = malloc(sizeof(char *) * (count_total_args(command) + 1));
	argv->idx = 0;
}

int	check_op(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

void	div_and_free_sub(t_argv *argv, char *str, int start, int len)
{
	char	*sub;

	sub = ft_substr(str, start, len);
	if (check_op(sub))
		divide_op(sub, argv);
	else
		argv->data[argv->idx++] = ft_strdup(sub);
	free(sub);
}
