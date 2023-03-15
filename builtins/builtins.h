/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:13:03 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/15 14:18:39 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

void	exec_unset(char *argv[]);
void	exec_env(void);
void	exec_pwd(void);
int		exec_cd(char *argv[]);
void	exec_echo(char *argv[]);
void	exec_export(char *argv[]);

#endif
