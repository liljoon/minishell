/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_std_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:59:27 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/21 12:30:44 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_std_fd(int fd[])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
}

void	restore_std_fd(int fd[])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}
