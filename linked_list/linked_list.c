/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:57:26 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/07 00:05:08 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_node	*new_node(char *_data)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	ret->next = NULL;
	ret->data = malloc(sizeof(char) * (ft_strlen(_data) + 1));
	ft_strlcpy(ret->data, _data, ft_strlen(_data) + 1);
	return (ret);
}

void	del_node(t_node *node)
{
	free(node->data);
	free(node);
}

void	push_back(t_node **head, char *_data)
{
	t_node	*idx;

	if (*head == NULL)
	{
		*head = new_node(_data);
		return ;
	}
	idx = *head;
	while (idx->next != NULL)
		idx = idx->next;
	idx->next = new_node(_data);
}

void	del_all_node(t_node **head)
{
	t_node	*idx;
	t_node	*before;

	idx = *head;
	while (idx != NULL)
	{
		before = idx;
		idx = idx->next;
		del_node(before);
	}
	*head = NULL;
}
