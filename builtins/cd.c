/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:21:07 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 22:21:20 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exec_cd(char *argv[])
{
	char	*temp_dir;

	temp_dir = getcwd(NULL, 0);
	if (argv[1] == NULL)
		chdir(my_getenv("HOME"));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		chdir(my_getenv("OLDPWD"));
	else if (argv[1][0] == '~')
	{
		if (chdir(ft_strjoin(my_getenv("HOME"), &(argv[1][1]))) == -1)
			printf_err(argv[0], argv[1], strerror(errno));
	}
	else if (chdir(argv[1]) == -1)
		printf_err(argv[0], argv[1], strerror(errno));
	modify_env("OLDPWD", temp_dir);
	free(temp_dir);
	return ;
}
