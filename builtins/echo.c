/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:20:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 22:20:59 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exec_echo(char *argv[])
{
	int		idx;

	idx = 1;
	if (argv[1] && ft_strncmp("-n", argv[1], 3) == 0)
		idx = 2;
	while (argv[idx])
	{
		printf("%s", argv[idx]);
		if (argv[idx + 1] != NULL)
			printf(" ");
		idx++;
	}
	if (!(argv[1] && ft_strncmp("-n", argv[1], 3) == 0))
		printf("\n");
	return ;
}
