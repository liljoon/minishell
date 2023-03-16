/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:59:35 by yham              #+#    #+#             */
/*   Updated: 2023/03/16 21:21:43 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	divide_op(char *str, t_argv *argv)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += step_to_last_quote(str, i, str[i]);
		else if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0)
				argv->data[argv->idx++] = ft_substr(str, start, i - start);
			start = i;
			i += step_to_last_redir(str, i, str[i]);
			if (str[i + 1])
			{
				argv->data[argv->idx++] = ft_substr(str, start, i - start + 1);
				start = i + 1;
			}
		}
		i++;
	}
	argv->data[argv->idx++] = ft_substr(str, start, i - start);
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
		if (command[i] == '\'' || command[i] == '\"')
			i += step_to_last_quote(command, i, command[i]);
		else if (command[i] == ' ')
		{
			if (i > 0)
				div_and_free_sub(&argv, command, \
											start, i - start);
			i += step_to_last_space(command, i);
			start = i + 1;
		}
		i++;
	}
	div_and_free_sub(&argv, command, start, i - start);
	argv.data[argv.idx] = NULL;
	return (argv.data);
}
