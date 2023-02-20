# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 13:47:44 by isunwoo           #+#    #+#              #
#    Updated: 2023/02/19 22:24:35 by isunwoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	#-Wall -Wextra -Werror

SRCS	=	main.c	sig_handle.c	exec_command.c	builtins1.c builtins2.c

INCS	=	minishell.h

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

READLINE_I = -I${HOME}/.brew/opt/readline/include

READLINE_L = -lreadline -L${HOME}/.brew/opt/readline/lib


.SUFFIXES : .c .o
.c.o :
	@$(CC) -g -c $(CFLAGS) $(READLINE_I) $< -o $@

$(NAME)	:	$(OBJS)
	@make -C ./libft
	@$(CC) -g $(OBJS) $(READLINE_L) -L./libft -lft -o $@

all	: $(NAME)

clean :
	@make clean -C ./libft
	@rm -f $(OBJS)

fclean : clean
	@make fclean -C ./libft
	@rm -f $(NAME) $(OBJS)

re :
	@make fclean
	@make $(NAME)

.PHONY : all clean fclean re
