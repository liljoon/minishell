/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:07:09 by yham              #+#    #+#             */
/*   Updated: 2023/03/24 17:55:16 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**extract_new_argv(char *command, char **old_argv)
{
	int		i;
	int		new_idx;
	char	**new_argv;

	new_argv = ft_calloc(count_total_args(command) - count_op(old_argv) + 1, \
							sizeof(char *));
	i = 0;
	new_idx = 0;
	while (old_argv[i])
	{
		if (is_redir(old_argv[i][0]))
		{
			if (!old_argv[++i] || is_redir(old_argv[i][0]))
				continue ;
		}
		else
			new_argv[new_idx++] = my_strdup(old_argv[i]);
		if (new_idx > 0 && !new_argv[new_idx - 1])
			new_idx--;
		i++;
	}
	new_argv[new_idx] = NULL;
	return (new_argv);
}

int	handle_op_error(char **new_argv, char **operator)
{
	if (new_argv)
		free_chars(new_argv);
	if (operator)
		free_chars(operator);
	return (1);
}

int	extract_op(t_token *tk, char **old_argv, char **new_argv)
{
	int		i;
	int		op_idx;
	char	**operator;

	operator = ft_calloc((count_op(old_argv) * 2 + 1), sizeof(char *));
	i = 0;
	op_idx = 0;
	while (old_argv[i])
	{
		if (is_redir(old_argv[i][0]))
		{
			operator[op_idx++] = ft_strdup(old_argv[i]);
			if (!old_argv[++i])
				return (handle_op_error(new_argv, operator));
			operator[op_idx] = my_strdup(old_argv[i]);
			if (!old_argv[i] || !operator[op_idx] \
				|| is_redir(operator[op_idx][0]))
				return (handle_op_error(new_argv, operator));
			else
				op_idx++;
		}
		i++;
	}
	operator[op_idx] = NULL;
	init_token(tk, new_argv, operator);
	return (0);
}
