/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:22:06 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 14:49:19 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exec_unset(char *argv[])
{
	argv++;
	while (*argv)
	{
		find_and_del_env(*argv);
		argv++;
	}
	g_shell_info.exit_status = 0;
}
