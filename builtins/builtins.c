/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:06:13 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 14:50:33 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_builtins(t_token *tk)
{
	if (ft_strncmp(tk->cmd, "echo", 5) == 0)
		exec_echo(tk->argv);
	else if (ft_strncmp(tk->cmd, "cd", 3) == 0)
		exec_cd(tk->argv);
	else if (ft_strncmp(tk->cmd, "pwd", 4) == 0)
		exec_pwd();
	else if (ft_strncmp(tk->cmd, "export", 7) == 0)
		exec_export(tk->argv);
	else if (ft_strncmp(tk->cmd, "unset", 6) == 0)
		exec_unset(tk->argv);
	else if (ft_strncmp(tk->cmd, "env", 4) == 0)
		exec_env();
	else if (ft_strncmp(tk->cmd, "exit", 5) == 0)
		exec_exit(tk->argv);
	else
		return (0);
	return (1);
}
