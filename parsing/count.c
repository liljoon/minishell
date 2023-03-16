/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:51:52 by yham              #+#    #+#             */
/*   Updated: 2023/03/16 15:28:56 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_arg_in_str(char *str)
{
	int		i;
	int		arg;

	i = 0;
	arg = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += step_to_last_quote(str, i, str[i]);
		else if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0)
				arg++;
			i += step_to_last_redir(str, i, str[i]);
			arg++;
		}
		i++;
	}
	arg++;
	return (arg);
}

int	count_total_args(char *str)
{
	int		i;
	int		args;
	int		start_idx;
	char	*sub;

	i = 0;
	args = 0;
	start_idx = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += step_to_last_quote(str, i, str[i]);
		else if (str[i] == ' ')
		{
			if (i > 0)
				args += malloc_and_free_sub(str, start_idx, i - start_idx);
			i += step_to_last_space(str, i);
			start_idx = i + 1;
		}
		i++;
	}
	args += malloc_and_free_sub(str, start_idx, i - start_idx);
	return (args);
}

int	count_op(char **argv)
{
	int	i;
	int	j;
	int	op;

	i = 0;
	op = 0;
	while (argv[i])
	{
		if (argv[i][0] == '<' || argv[i][0] == '>')
			op++;
		i++;
	}
	return (op);
}
