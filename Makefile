# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 13:47:44 by isunwoo           #+#    #+#              #
#    Updated: 2023/02/20 20:57:04 by isunwoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	#-Wall -Wextra -Werror

SRCS	=	main.c	sig_handle.c	exec_command.c	builtins1.c builtins2.c	utils.c

INCS	=	minishell.h

NAME	=	minishell

READLINE_I = -I${HOME}/.brew/opt/readline/include

READLINE_L = -lreadline -L${HOME}/.brew/opt/readline/lib

$(NAME)	:	$(SRCS) $(INCS)
	@make -C ./libft
	@$(CC) -g $(SRCS) $(CFLAGS) $(READLINE_I) $(READLINE_L) -L./libft -lft -o $@

all	: $(NAME)

clean :
	@make clean -C ./libft

fclean : clean
	@make fclean -C ./libft
	@rm -f $(NAME) $(OBJS)

re :
	@make fclean
	@make $(NAME)

.PHONY : all clean fclean re
