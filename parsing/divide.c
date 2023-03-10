/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:59:35 by yham              #+#    #+#             */
/*   Updated: 2023/03/10 17:06:53 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	divide_op(char *str, char **argv, int argv_idx)
{
	int		i;
	int		start_idx;
	int		cnt;

	i = 0;
	start_idx = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (i > 0)
			{
				argv[argv_idx + cnt] = ft_substr(str, start_idx, i - start_idx);
				cnt++;
			}
            start_idx = i;
			if ((str[i] == '<' && str[i + 1] && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>'))
				i++;
            argv[argv_idx + cnt] = ft_substr(str, start_idx, i - start_idx + 1);
			cnt++;
			start_idx = ++i;
			continue ;
		}
		i++;
	}
	if (str[i - 1] && str[i - 1] != '<' && str[i- 1] != '>')
	{
		argv[argv_idx + cnt] = ft_substr(str, start_idx, i - start_idx);
		cnt++;
	}
	return (cnt);
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

char	**divide_argv(char *command)
{
	int		i;
	int		start_idx;
	int		argv_idx;
	char	*sub;
	char	**argv;

	argv = malloc(sizeof(char *) * (count_total_args(command) + 1));
	i = 0;
	start_idx = 0;
	argv_idx = 0;
	while (command[i])
	{
		if (command[i] == ' ')
		{
			if (i > 0)
			{
				sub = ft_substr(command, start_idx, i - start_idx);
				if (check_op(sub))
					argv_idx += divide_op(sub, argv, argv_idx);
				else
					argv[argv_idx++] = ft_strdup(sub);
				free(sub);
			}
			while (command[i] == ' ')
				i++;
			start_idx = i;
			continue ;
		}
		i++;
	}
	sub = ft_substr(command, start_idx, i - start_idx);
	if (check_op(sub))
		argv_idx += divide_op(sub, argv, argv_idx);
	else
		argv[argv_idx++] = ft_strdup(sub);
	free(sub);
	argv[argv_idx] = NULL;
	return (argv);
}
