/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:21:57 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 21:07:05 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_err(char *arg0, char *arg1, char *err)
{
	write(2, "minishell: ", 12);
	write(2, arg0, ft_strlen(arg0));
	write(2, ": ", 2);
	if (arg1)
	{
		write(2, arg1, ft_strlen(arg1));
		write(2, ": ", 2);
	}
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}
