/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:21:07 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 14:48:41 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	err_handle(char *argv[], int *flag)
{
	printf_err(argv[0], argv[1], strerror(errno));
	*flag = 1;
}

void	exec_cd(char *argv[])
{
	char	*temp_dir;
	char	*to_dir;
	int		err_flag;

	err_flag = 0;
	temp_dir = getcwd(NULL, 0);
	if (argv[1] == NULL || ft_strncmp(argv[1], "--", 3) == 0)
		chdir(my_getenv("HOME"));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		chdir(my_getenv("OLDPWD"));
	else if (argv[1][0] == '~')
	{
		to_dir = ft_strjoin(my_getenv("HOME"), &(argv[1][1]));
		if (chdir(to_dir) == -1)
			err_handle(argv, &err_flag);
		free(to_dir);
	}
	else if (chdir(argv[1]) == -1)
		err_handle(argv, &err_flag);
	modify_env("OLDPWD", temp_dir);
	free(temp_dir);
	if (err_flag)
		g_shell_info.exit_status = 1;
	else
		g_shell_info.exit_status = 0;
}
