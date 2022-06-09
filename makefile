# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhammani <yhammani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 22:21:13 by yhammani          #+#    #+#              #
#    Updated: 2022/05/31 22:21:16 by yhammani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo/philo

B_NAME	=	philo_bonus/philo_bonus

H		=	philo/philo.h

B_H		=	philo_bonus/philo_bonus.h

SRCS	=	$(addprefix philo/, philo.c actions.c threads.c utils.c)

B_SRCS	=	$(addprefix philo_bonus/, philo_bonus.c actions_bonus.c \
			processes_bonus.c utils_bonus.c)

OBJS	=	$(SRCS:.c=.o)

B_OBJS	=	$(B_SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

all		:	$(NAME)

bonus	:	$(B_NAME)

$(NAME)	:	$(OBJS) $(H)
			@cc $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
			@echo philo is ready to go

$(B_NAME)	:	$(B_OBJS) $(B_H)
			@cc $(CFLAGS) -lpthread $(B_OBJS) -o $(B_NAME)
			@echo philo_bonus is ready to go

.c.o	:	$(SRCS) $(B_SRCS) $(B_H) $(H)
			@cc $(CFLAGS) -c $^ -o $(^:.c=.o)
			@echo Compiling $^

clean	:
			@rm -f $(OBJS) $(B_OBJS)
			@echo object files are removed

fclean	:	clean
			@rm -f $(NAME) $(B_NAME)
			@echo Executables are removed

re		:	fclean all

.PHONY	:	clean fclean all re bonus
