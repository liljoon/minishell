/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:51:25 by yham              #+#    #+#             */
/*   Updated: 2023/03/24 17:54:39 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_token(t_token *tk, char **_argv, char **_operator)
{
	tk->argv = _argv;
	tk->operator = _operator;
	tk->cmd = tk->argv[0];
	tk->heredoc_fd = -1;
	tk->next = NULL;
}

void	init_token_null(t_token *tk)
{
	tk->argv = malloc(sizeof(char **));
	tk->argv[0] = NULL;
	tk->operator = malloc(sizeof(char **));
	tk->operator[0] = NULL;
	tk->cmd = tk->argv[0];
	tk->next = NULL;
}

void	handle_syntax_error(t_token *tk)
{
	init_token_null(tk);
	printf_err(NULL, NULL, "syntax error");
	g_shell_info.exit_status = 258;
}

t_token	*tokenize(char *command, int err_flag)
{
	char	**old_argv;
	char	**new_argv;
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	if (err_flag || check_exceptions(command))
	{
		handle_syntax_error(tk);
		return (tk);
	}
	old_argv = divide_argv(command);
	new_argv = extract_new_argv(command, old_argv);
	if (extract_op(tk, old_argv, new_argv))
		handle_syntax_error(tk);
	free_chars(old_argv);
	return (tk);
}
