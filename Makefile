# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yham <yham@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 13:47:44 by isunwoo           #+#    #+#              #
#    Updated: 2023/03/10 17:45:30 by yham             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	=	#-Wall -Wextra -Werror

BUILTINS_SRC	=	builtins/*.c
PARSING_SRC		=	parsing/*.c

SRCS	=	main.c	$(BUILTINS_SRC) $(PARSING_SRC)	sig_handle.c	exec_command.c \
			redirections.c	environ_func.c	linked_list/linked_list.c	pipe.c \
			control_std_fd.c  free.c	parsing_pipe.c	error.c

TEST_SRCS = test.c	$(BUILTINS_SRC) $(PARSING_SRC)	sig_handle.c	exec_command.c	\
			redirections.c	environ_func.c	linked_list/linked_list.c	pipe.c \
			control_std_fd.c  free.c	parsing_pipe.c	error.c


INCS	=	minishell.h	linked_list/linked_list.h builtins/builtins.h

NAME	=	minishell

ON_CLUSTER = 0

ifeq ($(ON_CLUSTER) , 0)
	READLINE_I = -I/opt/homebrew/opt/readline/include

	READLINE_L = -lreadline -L/opt/homebrew/opt/readline/lib
else
	READLINE_I = -I/Users/$(USER)/.brew/opt/readline/include

	READLINE_L = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
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
