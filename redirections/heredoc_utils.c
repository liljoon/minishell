/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:12:30 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 22:17:25 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_on(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void	echo_off(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}
