/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:07:09 by yham              #+#    #+#             */
/*   Updated: 2023/03/17 18:14:10 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**extract_new_argv(char *command, char **old_argv)
{
	int		i;
	int		new_idx;
	char	**new_argv;

	new_argv = malloc(sizeof(char *) * \
				(count_total_args(command) - (count_op(old_argv) * 2) + 1));
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
			new_argv[new_idx] = my_strdup(old_argv[i]);
		if (new_argv[new_idx])
			new_idx++;
		i++;
	}
	new_argv[new_idx] = NULL;
	return (new_argv);
}

char	*handle_op_error(char **operator, int idx)
{
	printf_err(NULL, NULL, "syntax error");
	operator[idx] = NULL;
	free_chars(operator);
	return (NULL);
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
			operator[op_idx++] = ft_strdup(old_argv[i]);
			i++;
			operator[op_idx] = my_strdup(old_argv[i]);
			if (!old_argv[i] || !operator[op_idx] \
				|| operator[op_idx][0] == '<' || operator[op_idx][0] == '>')
				return (handle_op_error(operator, op_idx));
			else
				op_idx++;
		}
		i++;
	}
	operator[op_idx] = NULL;
	return (operator);
}
