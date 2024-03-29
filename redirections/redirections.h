/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:42:48 by isunwoo           #+#    #+#             */
/*   Updated: 2023/03/24 22:17:15 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H
# include "../minishell.h"

void	set_heredoc(t_token *tk);
void	sigint_handler_heredoc(int signo);

void	echo_on(void);
void	echo_off(void);

#endif
