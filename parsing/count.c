/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:51:52 by yham              #+#    #+#             */
/*   Updated: 2023/03/10 20:46:37 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_space(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (str[i])
	{
		if (str[i] == ' ')
        {
            while (str[i + 1] && str[i + 1] != ' ')
                i++;
            space++;
        }
		i++;
	}
	return (space);
}

int	count_arg_in_str(char *str)
{
	int		i;
	int		arg;
	char	quote;

	i = 0;
	arg = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else
				quote = 0;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (quote)
			{
				i++;
				continue ;
			}
			if (i > 0)
				arg++;
			while ((str[i] == '<' && str[i + 1] && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>'))
				i++;
			arg++;
		}
		i++;
	}
	if (str[i - 1] && str[i - 1] != '<' && str[i - 1] != '>')
		arg++;
	return (arg);
}

int	count_total_args(char *str)
{
	int		i;
	int		args;
	int		start_idx;
	char	quote;
	char	*sub;

	i = 0;
	args = 0;
	start_idx = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else
				quote = 0;
		}
		else if (str[i] == ' ')
		{
			if (quote)
			{
				i++;
				continue ;
			}
			if (i > 0)
			{
				sub = ft_substr(str, start_idx, i - start_idx);
				args += count_arg_in_str(sub);
				free(sub);
			}
			while (str[i] == ' ')
				i++;
			start_idx = i;
			continue ;
		}
		i++;
	}
	sub = ft_substr(str, start_idx, i - start_idx);
	args += count_arg_in_str(sub);
	free(sub);
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
