# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calle <calle@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 16:50:27 by calle             #+#    #+#              #
#    Updated: 2021/01/04 17:15:09 by calle            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

HEADERS = ft_printf.h

CC = clang-9

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
		make -C libft/
		ar rcs $@ $^ libft/libft.a

clean :
		clean -C libft/
		rm -f $(OBJS)

fclean : clean
		 fclean -C libft/
		 rm -f $(NAME)

re : fclean all
