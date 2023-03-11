/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:20:53 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/10 17:57:54 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_option(char *option)
{
	if (option == NULL)
		return (0);
	if (ft_strncmp("-n", option, 2) == 0)
	{
		option++;
		while (*option)
		{
			if (*option != 'n')
				return (0);
			option++;
		}
	}
	return (1);
}

void	exec_echo(char *argv[])
{
	int		idx;
	int		is_n_option;

	is_n_option = check_option(argv[1]);
	idx = 1 + is_n_option;
	while (argv[idx])
	{
		printf("%s", argv[idx]);
		if (argv[idx + 1] != NULL)
			printf(" ");
		idx++;
	}
	if (!is_n_option)
		printf("\n");
	return ;
}
