/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:13:03 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 14:48:50 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

void	exec_unset(char *argv[]);
void	exec_env(void);
void	exec_exit(char **argv);
void	exec_pwd(void);
void	exec_cd(char *argv[]);
void	exec_echo(char *argv[]);
void	exec_export(char *argv[]);
char	**split_env(char *str);
int		count_string_arr_len(char **strings);
#endif
