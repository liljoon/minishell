/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:59:35 by yham              #+#    #+#             */
/*   Updated: 2023/03/21 20:22:56 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_argv(t_argv *argv, char *command)
{
	argv->data = malloc(sizeof(char *) * (count_total_args(command) + 1));
	argv->idx = 0;
}

char	**divide_argv(char *command)
{
	int		i;
	int		start;
	t_argv	argv;

	init_argv(&argv, command);
	i = 0;
	start = 0;
	while (command[i])
	{
		if (is_quote(command[i]))
			i += step_to_last_quote(command, i, command[i]);
		else if (is_space(command[i]))
		{
			if (i > 0)
				divide_and_free_sub(&argv, command, \
											start, i - start);
			i += step_to_last_space(command, i);
			start = i + 1;
		}
		i++;
	}
	if (i > 0 && !(is_quote(command[i - 1]) || is_space(command[i - 1])))
		divide_and_free_sub(&argv, command, start, i - start);
	argv.data[argv.idx] = NULL;
	return (argv.data);
}
