/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 21:57:08 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/26 17:15:19 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_node	t_node;
struct s_node
{
	char	*data;
	t_node	*next;
}	;

void	push_back(t_node **head, char *_data);
void	find_and_del_node(t_node **head, char *_data);
void	del_all_node(t_node **head);


#endif
