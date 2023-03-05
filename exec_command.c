/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:36:25 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/05 18:52:51 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(char *argv[])
{
	char	*path;
	char	**paths;
	char	*old_argv0;

	if (argv[0][0] == '/')
	{
		execve(argv[0], argv, get_envp());
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
			execve(argv[0], argv, get_envp());
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

void	exec_command(t_token *tk)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		check_redirections(tk);
		check_path(tk->argv);
		exit(127);
	}
	else
	{
		waitpid(pid, &g_shell_info.exit_status, 0);
		g_shell_info.exit_status /= 256;
	}
	return ;
}
