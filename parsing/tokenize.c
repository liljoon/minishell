/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:25 by yham              #+#    #+#             */
/*   Updated: 2023/03/17 15:07:23 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_token(t_token *tk, char **_argv, char **_operator)
{
	tk->argv = _argv;
	tk->operator = _operator;
	tk->cmd = tk->argv[0];
	tk->next = NULL;
}

t_token	*tokenize(char *command)
{
	char	**old_argv;
	char	**new_argv;
	char	**operator;
	t_token	*tk;

	if (check_exceptions(command))
		return (NULL);
	tk = malloc(sizeof(t_token));
	old_argv = divide_argv(command);
	new_argv = extract_new_argv(command, old_argv);
	operator = extract_op(old_argv);
	init_token(tk, new_argv, operator);
	free_chars(old_argv);
	return (tk);
}
