# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calle <calle@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 16:50:27 by calle             #+#    #+#              #
#    Updated: 2021/01/13 16:42:14 by calle            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = initiate_struct.c\
		itoa_base.c\
		mvp.c\
		utils.c
OBJS = $(SRCS:.c=.o)

HEADERS = -I ft_printf.h

CC = gcc

CFLAGS = -c -Wall -Werror -Wextra

LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
		$(MAKE) -C ./libft
		cp libft/libft.a $(NAME)
		$(CC) $(CFLAGS) $(HEADERS) $(SRCS)
		ar rcs $@ $^
clean :
		$(MAKE) clean -C ./libft
		rm -f $(OBJS)

fclean : clean
		 $(MAKE) fclean -C ./libft
		 rm -f $(NAME)

re : fclean all
