/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:16:01 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 15:08:08 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	trim_splited_command(char **spl_cmd)
{
	char	*temp;

	while (*spl_cmd)
	{
		temp = *spl_cmd;
		*spl_cmd = ft_strtrim(*spl_cmd, " ");
		free(temp);
		spl_cmd++;
	}
}

void	substitute_pipe(char *original)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (original[i])
	{
		if (original[i] == '\'' || original[i] == '\"')
		{
			if (quote == 0)
				quote = original[i];
			else if (quote == original[i])
				quote = 0;
		}
		else if (original[i] == '|' && !quote)
			original[i] = -1;
		i++;
	}
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
