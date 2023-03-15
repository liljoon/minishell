/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:21:07 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/15 14:22:22 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_cd(char *argv[])
{
	char	*temp_dir;
	char	*to_dir;
	int		err_flag;

	err_flag = 0;
	temp_dir = getcwd(NULL, 0);
	if (argv[1] == NULL)
		chdir(my_getenv("HOME"));
	else if (ft_strncmp(argv[1], "-", 2) == 0)
		chdir(my_getenv("OLDPWD"));
	else if (ft_strncmp(argv[1], "--", 3) == 0)
		chdir(my_getenv("HOME"));
	else if (argv[1][0] == '~')
	{
		to_dir = ft_strjoin(my_getenv("HOME"), &(argv[1][1]));
		if (chdir(to_dir) == -1)
		{
			printf_err(argv[0], argv[1], strerror(errno));
			err_flag = 1;
		}
		free(to_dir);
	}
	else if (chdir(argv[1]) == -1)
	{
		printf_err(argv[0], argv[1], strerror(errno));
		err_flag = 1;
	}
	modify_env("OLDPWD", temp_dir);
	free(temp_dir);
	if (err_flag)
		return (1);
	return (0);
}
