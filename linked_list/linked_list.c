/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:57:26 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/26 17:54:35 by isunwoo          ###   ########.fr       */
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

void	find_and_del_node(t_node **head, char *_data)
{
	t_node	*temp;
	t_node	*before;

	temp = *head;
	if (*head == NULL)
		return ;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->data, _data, ft_strlen(_data)) == 0 && \
			(*(temp->data + ft_strlen(_data)) == '=' || *(temp->data + ft_strlen(_data)) == 0))
			break ;
		before = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	if (temp == *head)
		*head = temp->next;
	else
		before->next = temp->next;
	del_node(temp);
}

void	del_all_node(t_node **head)
{
	t_node	*idx;

	idx = *head;
	while (idx != NULL)
	{
		del_node(idx);
		idx = idx->next;
	}
	*head = NULL;
}
