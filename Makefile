# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktan <ktan@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 14:19:44 by ktan              #+#    #+#              #
#    Updated: 2023/02/04 00:17:00 by ktan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c \
		ft_checkfmt.c \
		ft_printfmt.c \
		ft_itoa_base.c

INC_DIR := includes/

OBJS		= $(SRCS:%.c=%.o)

LIBFT_DIR	= ./libft/

LIBFT		= $(LIBFT_DIR)libft.a

LIBS		= $(LIBFT)

CPPFLAGS 	= -I$(LIBFT_DIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs
RM = rm -f

all bonus: $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	cp $(LIBFT) .
	mv libft.a $@
	$(AR) $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) $@

fclean : clean
	$(RM) $(NAME) $(LIBFT)

re : fclean all

.PHONY: bonus all clean fclean re libft
