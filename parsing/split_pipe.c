/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:20:15 by yham              #+#    #+#             */
/*   Updated: 2023/03/24 21:22:25 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*handle_pipe_error(void)
{
	printf_err(NULL, NULL, "syntax error");
	g_shell_info.exit_status = 258;
	return (NULL);
}

void	push_back_tk(t_token **head, t_token *new_tk)
{
	t_token	*idx;

	if (*head == NULL)
	{
		*head = new_tk;
		return ;
	}
	idx = *head;
	while (idx->next != NULL)
		idx = idx->next;
	idx->next = new_tk;
}

t_token	*split_pipe_and_tokenize(char *command)
{
	t_token	*head;
	t_token	*new_tk;
	char	**splited_command;
	char	**temp;

	substitute_pipe(command);
	splited_command = ft_split(command, (char)-1);
	trim_splited_command(splited_command);
	if (check_pipe(command, splited_command))
		return (handle_pipe_error());
	head = NULL;
	temp = splited_command;
	while (*splited_command)
	{
		new_tk = tokenize(*splited_command);
		push_back_tk(&head, new_tk);
		splited_command++;
	}
	free_chars(temp);
	return (head);
}
