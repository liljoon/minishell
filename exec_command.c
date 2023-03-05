/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:36:25 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/03 15:10:01 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(char *argv[], char *envp[])
{
	char	*path;
	char	**paths;
	char	*old_argv0;

	if (argv[0][0] == '/')
	{
		execve(argv[0], argv, envp);
		printf("minishell: %s: %s\n", argv[0], strerror(errno));
	}
	else
	{
		old_argv0 = argv[0];
		path = getenv("PATH");
		paths = ft_split(path, ':');
		while (*paths)
		{
			argv[0] = old_argv0;
			argv[0] = ft_strjoin("/", argv[0]);
			argv[0] = ft_strjoin(*paths, argv[0]);
			execve(argv[0], argv, envp);
			paths++;
		}
		printf("minishell: %s: command not found\n", old_argv0);
	}
}

void	trans_env(char *argv[])
{
	while (*argv)
	{
		if ((*argv)[0] == '$')
		{
			if ((*argv)[1] == '?')
				*argv = ft_itoa(g_shell_info.exit_status);
			else
				*argv = getenv(&(*argv)[1]);
		}
		argv++;
	}
}

void	exec_command(char *command, char *envp[])
{
	pid_t	pid;
	char	**argv;


	pid = fork();
	if (pid == 0)
	{
		//command = check_redirection_output(command);
		argv = ft_split(command, ' ');
		if (*argv == NULL)
			exit(0);
		trans_env(argv);
		check_path(argv, envp);
		exit(127);
	}
	else
	{
		waitpid(pid, &g_shell_info.exit_status, 0);
		g_shell_info.exit_status /= 256;
	}
	return ;
}
