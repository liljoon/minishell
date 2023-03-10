/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:25 by yham              #+#    #+#             */
/*   Updated: 2023/03/10 17:07:27 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	tokenize(char *command)
t_token	*tokenize(char *command)
{
	int		i;
	char	**old_argv;
	char	**new_argv;
	char	**operator;
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	// printf("args:%d\n", count_total_args(command));
	old_argv = divide_argv(command);
	new_argv = extract_new_argv(command, old_argv);
	operator = extract_op(old_argv);
	tk->argv = new_argv;
	tk->operator = operator;
	tk->cmd = tk->argv[0];
	tk->next = NULL;
	// i = -1;
	// while (old_argv[++i])
	// 	printf("old:%s\n", old_argv[i]);
	// i = -1;
	// while (new_argv[++i])
	// 	printf("new:%s\n", new_argv[i]);
	// i = -1;
	// while (operator[++i])
	// 	printf("op:%s\n", operator[i]);
	free_chars(old_argv);
	return (tk);
}
