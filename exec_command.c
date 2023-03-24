/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:36:25 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 18:07:37 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path_and_exec(char *argv[])
{
	char	*path;
	char	**paths;
	char	*old_argv0;

	if (!ft_isalnum(argv[0][0]))
	{
		execve(argv[0], argv, get_envp());
		printf_err(argv[0], NULL, strerror(errno));
	}
	else
	{
		old_argv0 = argv[0];
		path = my_getenv("PATH");
		paths = ft_split(path, ':');
		while (*paths)
		{
			argv[0] = old_argv0;
			argv[0] = ft_strjoin("/", argv[0]);
			argv[0] = ft_strjoin(*paths, argv[0]);
			execve(argv[0], argv, get_envp());
			paths++;
		}
		printf_err(old_argv0, NULL, "command not found");
	}
	exit(127);
}

void	fork_and_exec(t_token *tk)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		check_path_and_exec(tk->argv);
	else
	{
		waitpid(pid, &g_shell_info.exit_status, 0);
		g_shell_info.exit_status = WEXITSTATUS(g_shell_info.exit_status);
	}
	return ;
}

int	count_linked_list(t_token *tks)
{
	int	idx;

	idx = 0;
	while (tks)
	{
		idx++;
		tks = tks->next;
	}
	return (idx);
}

void	exec_control(t_token *tks)
{
	int		len;

	len = count_linked_list(tks);
	if (len == 0)
		return ;
	if (scan_heredoc_all(tks))
		return ;
	if (len == 1)
	{
		if (!check_redirections(tks, tks->operator) \
			&& *(tks->argv) && !exec_builtins(tks))
			fork_and_exec(tks);
	}
	else
	{
		set_pipe_and_exec(tks, len);
		while (tks)
		{
			if (tks->heredoc_fd != -1)
				close(tks->heredoc_fd);
			tks = tks->next;
		}
	}
}
