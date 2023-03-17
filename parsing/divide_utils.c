/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:19:52 by yham              #+#    #+#             */
/*   Updated: 2023/03/17 15:06:57 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	divide_and_free_sub(t_argv *argv, char *str, int start, int len)
{
	char	*sub;

	sub = ft_substr(str, start, len);
	if (check_op(sub))
		divide_op(sub, argv);
	else
		argv->data[argv->idx++] = ft_strdup(sub);
	free(sub);
}
