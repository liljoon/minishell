/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:25:41 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/05 20:27:38 by isunwoo          ###   ########.fr       */
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
}
