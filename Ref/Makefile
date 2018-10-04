# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncollie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 12:19:53 by ncollie           #+#    #+#              #
#    Updated: 2018/10/02 12:36:29 by ncollie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 
FILES = main.c main2.c print_me.c filecheck.c libft.a libftprintf.a
OBJECTS = $(FILES:.c=.o)

all:
	gcc -Wall -Werror -Wextra -I. $(FILES) -g -fsanitize=address
