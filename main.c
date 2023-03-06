/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:01:17 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/07 00:02:54 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*command;
	t_token	*tks;
	t_token	*idx;
	int		std_fd[2];

	set_signal();
	init_environ(envp);
	while (1)
	{
		command = readline("minishell$ ");
		if (!command)
		{
			printf("\033[1A");
			printf("\033[11C");
			printf("exit\n");
			exit(0);
		}
		if (command && *command)
			add_history(command);
		if (!*command)
			continue ;
		copy_std_fd(std_fd);

		tks = split_pipe_and_tokenize(command);
		idx = tks;
		while (idx)
		{
			check_redirections(idx);
			if (!exec_builtins(idx))
				exec_command(idx);
			idx = idx->next;
		}
		free_all_tks(&tks);
		free(command);
		restore_std_fd(std_fd);
	}
}
