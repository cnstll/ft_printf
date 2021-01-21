# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calle <calle@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 16:50:27 by calle             #+#    #+#              #
#    Updated: 2021/01/21 12:21:38 by calle            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = srcs/initiate_struct.c\
		srcs/itoa_base.c\
		srcs/utils.c\
		srcs/shared.c\
		srcs/shared_2.c\
		srcs/convert_tree.c\
		srcs/convert_c_s.c\
		srcs/convert_u_d_i.c\
		srcs/convert_p.c\
		srcs/convert_x.c\
		srcs/convert_percent.c\
		srcs/ft_printf.c

OBJS = $(SRCS:.c=.o)

HEADERS = includes

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB = -L./libft/ -lft

all : $(NAME)

$(NAME) : $(OBJS)
		$(MAKE) -C ./libft
		cp libft/libft.a ./$(NAME)
		ar rcs $@ $^

bonus : ${NAME}

%.o : %.c
		@${CC} ${CFLAGS} -I ${HEADERS} -o  $@ -c $<

clean :
		$(MAKE) clean -C ./libft
		rm -f $(OBJS)

fclean : clean
		 $(MAKE) fclean -C ./libft
		 rm -f $(NAME)

re : fclean all
