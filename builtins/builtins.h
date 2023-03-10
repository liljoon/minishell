/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:13:03 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/09 22:16:17 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_unset(char *argv[]);
void	exec_env(void);
void	exec_pwd(void);
void	exec_cd(char *argv[]);
void	exec_echo(char *argv[]);
void	exec_export(char *argv[]);
