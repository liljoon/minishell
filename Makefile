# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 13:47:44 by isunwoo           #+#    #+#              #
#    Updated: 2023/02/26 17:18:52 by isunwoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	#-Wall -Wextra -Werror

SRCS	=	main.c	sig_handle.c	exec_command.c	builtins1.c builtins2.c	utils.c\
			redirections.c	environ_func.c	linked_list/linked_list.c

TEST_SRCS = test.c	sig_handle.c	exec_command.c	builtins1.c builtins2.c	utils.c\
			redirections.c	environ_func.c	linked_list/linked_list.c

INCS	=	minishell.h	linked_list/linked_list.h

NAME	=	minishell

ON_CLUSTER = 0

ifeq ($(ON_CLUSTER) , 0)
	READLINE_I = -I/opt/homebrew/opt/readline/include

	READLINE_L = -lreadline -L/opt/homebrew/opt/readline/lib
else
	READLINE_I = -I/Users/isunwoo/.brew/opt/readline/include

	READLINE_L = -lreadline -L/Users/isunwoo/.brew/opt/readline/lib
endif

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
