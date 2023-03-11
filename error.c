/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:21:57 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/10 18:31:33 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_err(char *arg0, char *arg1, char *err)
{
	write(2, "minishell: ", 12);
	if (arg0)
	{
		write(2, arg0, ft_strlen(arg0));
		write(2, ": ", 2);
	}
	if (arg1)
	{
		write(2, arg1, ft_strlen(arg1));
		write(2, ": ", 2);
	}
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}
