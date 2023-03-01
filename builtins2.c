/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:17:56 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/01 16:13:18 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char *argv[])
{
	while (*argv)
	{
		find_and_del_env(*argv);
		argv++;
	}
}

void	exec_env(void)
{
	print_all_env();
}
