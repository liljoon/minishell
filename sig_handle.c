/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:00:02 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 19:08:38 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	g_shell_info.exit_status = 1;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int signo)
{
	if (signo != SIGQUIT)
		return ;
	rl_redisplay();
	return ;
}

void	set_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
}

void	sig_handle_exec(int signo)
{
	if (signo == SIGINT)
		printf("\n");
	else if (signo == SIGQUIT)
		printf("Quit: %d\n", signo);
	return ;
}

void	set_signal_before_exec(void)
{
	signal(SIGINT, sig_handle_exec);
	signal(SIGQUIT, sig_handle_exec);
}
