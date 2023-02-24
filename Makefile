# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 13:47:44 by isunwoo           #+#    #+#              #
#    Updated: 2023/02/24 20:21:13 by isunwoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	#-Wall -Wextra -Werror

SRCS	=	main.c	sig_handle.c	exec_command.c	builtins1.c builtins2.c	utils.c\
			redirections.c

TEST_SRCS = test.c	sig_handle.c	exec_command.c	builtins1.c builtins2.c	utils.c\
			redirections.c

INCS	=	minishell.h

NAME	=	minishell

READLINE_I = -I/opt/homebrew/opt/readline/include

READLINE_L = -lreadline -L/opt/homebrew/opt/readline/lib

$(NAME)	:	$(SRCS) $(INCS)
	@make -C ./libft
	@$(CC) -g $(SRCS) $(CFLAGS) $(READLINE_I) $(READLINE_L) -L./libft -lft -o $@

test	: $(TEST_SRCS) $(INCS)
	@make -C ./libft
	@$(CC) -g $(TEST_SRCS) $(CFLAGS) $(READLINE_I) $(READLINE_L) -L./libft -lft -o $@

all	: $(NAME)

clean :
	@make clean -C ./libft

fclean : clean
	@make fclean -C ./libft
	@rm -f $(NAME) test

re :
	@make fclean
	@make $(NAME)

.PHONY : all clean fclean re
