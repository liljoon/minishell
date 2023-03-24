/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:20:15 by yham              #+#    #+#             */
/*   Updated: 2023/03/24 18:02:33 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

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
	int		err_flag;
	t_token	*head;
	t_token	*new_tk;
	char	**splited_command;
	char	**temp;

	substitute_pipe(command);
	splited_command = ft_split(command, (char)-1);
	trim_splited_command(splited_command);
	err_flag = check_pipe(command, splited_command);
	head = NULL;
	temp = splited_command;
	while (*splited_command)
	{
		if (*splited_command[0])
		{
			new_tk = tokenize(*splited_command, err_flag);
			push_back_tk(&head, new_tk);
		}
		splited_command++;
	}
	free_chars(temp);
	return (head);
}
