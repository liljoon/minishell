/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:25:41 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/07 00:04:01 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_chars(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		free(chars[i]);
		i++;
	}
	free(chars);
}

void	free_token(t_token *tk)
{
	free_chars(tk->argv);
	free_chars(tk->operator);
	free(tk);
}

void	free_all_tks(t_token **head)
{
	t_token	*idx;
	t_token	*before;

	idx = *head;
	while (idx != NULL)
	{
		before = idx;
		idx = idx->next;
		free_token(before);
	}
	*head = NULL;
}
