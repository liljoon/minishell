/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:35:04 by isunwoo           #+#    #+#             */
/*   Updated: 2023/02/20 17:07:31 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trans_command_to_env(char *command)
{
	char	*ret;
	int		idx_start;
	int		len;

	ret = malloc(1 * sizeof(char));
	ret[0] = '\0';
	idx_start = 0;
	len = 0;

	while (command[idx_start])
	{

	}
}
