/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:51:52 by yham              #+#    #+#             */
/*   Updated: 2023/03/21 20:21:48 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_arg_in_str(char *str)
{
	int		i;
	int		args;

	i = 0;
	args = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			i += step_to_last_quote(str, i, str[i]);
		else if (is_redir(str[i]))
		{
			if (i > 0)
				args++;
			i += step_to_last_redir(str, i, str[i]);
			if (str[i + 1])
				args++;
		}
		i++;
	}
	if (i > 0 && !(is_quote(str[i - 1])))
		args++;
	return (args);
}

int	count_total_args(char *str)
{
	int		i;
	int		args;
	int		start;

	i = 0;
	args = 0;
	start = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			i += step_to_last_quote(str, i, str[i]);
		else if (is_space(str[i]))
		{
			if (i > 0)
				args += count_and_free_sub(str, start, i - start);
			i += step_to_last_space(str, i);
			start = i + 1;
		}
		i++;
	}
	args += count_and_free_sub(str, start, i - start);
	return (args);
}

int	count_op(char **argv)
{
	int	i;
	int	op;

	i = 0;
	op = 0;
	while (argv[i])
	{
		if (is_redir(argv[i][0]))
			op++;
		i++;
	}
	return (op);
}
