/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:33:15 by yham              #+#    #+#             */
/*   Updated: 2023/03/10 18:47:23 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_exceptions(char *command)
{
    int i;
    int start;

    i = 0;
    while (command[i])
    {
        if (command[i] == '<' || command[i] == '>')
        {
            start = i;
            while ((command[i] == '<' && command[i + 1] && command[i + 1] == '<')
                    || (command[i] == '>' && command[i + 1] && command[i + 1] == '>'))
                i++;
            if (i - start + 1 > 2)
            {
                printf_err(NULL, NULL, "syntax error");
                return (1);
            }
        }
        i++;
    }
    return (0);
}
