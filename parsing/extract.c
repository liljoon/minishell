/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:07:09 by yham              #+#    #+#             */
/*   Updated: 2023/03/11 17:24:04 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strdup_without_quotes(const char *s1)
{
	int		i;
	int		j;
	int		s1_len;
	char	*p;

	s1_len = ft_strlen(s1);
	p = malloc(s1_len + 1);
	if (p == 0)
		return (p);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\'' || s1[i] == '\"')
		{
			i++;
			continue ;
		}
		p[j] = s1[i];
		i++;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	**extract_new_argv(char *command, char **old_argv)
{
	int		i;
	int		new_idx;
	char	quote;
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * (count_total_args(command) + 1 - count_op(old_argv) * 2 + 1));
	i = 0;
	new_idx = 0;
	while (old_argv[i])
	{
		if (old_argv[i][0] == '<' || old_argv[i][0] == '>')
		{
			if (!old_argv[i + 1])
				break ;
			i++;
		}
		else
			new_argv[new_idx++] = ft_strdup_without_quotes(old_argv[i]);
		i++;
	}
	new_argv[new_idx] = NULL;
	return (new_argv);
}

char	**extract_op(char **old_argv)
{
	int		i;
	int		op_idx;
	char	**operator;

	operator = malloc(sizeof(char *) * (count_op(old_argv) * 2 + 1));
	i = 0;
	op_idx = 0;
	while (old_argv[i])
	{
		if (old_argv[i][0] == '<' || old_argv[i][0] == '>')
		{
			operator[op_idx] = ft_strdup(old_argv[i]);
			op_idx++;
			i++;
			if (!old_argv[i])
				break ;
			operator[op_idx] = ft_strdup_without_quotes(old_argv[i]);
			op_idx++;
		}
		i++;
	}
	operator[op_idx] = NULL;
	return (operator);
}
