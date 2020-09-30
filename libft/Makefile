# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:49:24 by hthomas           #+#    #+#              #
#    Updated: 2020/09/30 14:37:32 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft.a
OBJS		=	${SRCS:.c=.o}
INCLUDES	=	includes
HEADER		=	$(INCLUDES)/libft.h
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

# io
SRCS		=	srcs/io/ft_print_tabint.c			\
				srcs/io/ft_putnbr.c					\
				srcs/io/ft_putnbr_fd.c				\
				srcs/io/ft_putnbr_unsigned_fd.c		\
				srcs/io/ft_putnbr_unsigned.c		\
				srcs/io/ft_putchar.c				\
				srcs/io/ft_putchar_fd.c				\
				srcs/io/ft_putendl_fd.c				\
				srcs/io/ft_puthex.c					\
				srcs/io/ft_putpointer.c				\
				srcs/io/ft_putstrn_fd.c				\
				srcs/io/ft_putstr_fd.c				\
				srcs/io/ft_putstr.c					\
				srcs/io/ft_putstrn.c				\
				srcs/io/ft_print_tabstr.c			\


# linked-list
SRCS		+=	srcs/linked-list/ft_lstnew.c		\
				srcs/linked-list/ft_lstadd_front.c	\
				srcs/linked-list/ft_lstsize.c		\
				srcs/linked-list/ft_lstlast.c		\
				srcs/linked-list/ft_lstadd_back.c	\
				srcs/linked-list/ft_lstdelone.c		\
				srcs/linked-list/ft_lstclear.c		\
				srcs/linked-list/ft_lstiter.c		\
				srcs/linked-list/ft_lstmap.c		\

# memory
SRCS		+=	srcs/memory/ft_swap.c				\
				srcs/memory/ft_memset.c				\
				srcs/memory/ft_memcpy.c				\
				srcs/memory/ft_memccpy.c			\
				srcs/memory/ft_memmove.c			\
				srcs/memory/ft_memchr.c				\
				srcs/memory/ft_memcmp.c				\
				srcs/memory/ft_calloc.c				\
				srcs/memory/ft_bzero.c				\
				srcs/memory/ft_chardup.c			\
				srcs/memory/ft_free_tab.c			\

# numeric
SRCS		+=	srcs/numeric/ft_nbrlen.c			\
				srcs/numeric/ft_convert_base.c		\
				srcs/numeric/ft_itoa.c				\
				srcs/numeric/ft_atol.c				\
				srcs/numeric/ft_uitoa.c				\
				srcs/numeric/ft_ltoa.c				\
				srcs/numeric/ft_ltoa_base.c			\
				srcs/numeric/ft_uitoa_base.c		\
				srcs/numeric/ft_itoa_width.c		\
				srcs/numeric/ft_pow.c				\
				srcs/numeric/ft_atoi.c				\
				srcs/numeric/ft_atoi_strict.c		\
				srcs/numeric/ft_atof.c				\
				srcs/numeric/ft_atoi_base.c			\
				srcs/numeric/ft_max_int.c			\
				srcs/numeric/ft_max_float.c			\
				srcs/numeric/ft_min_int.c			\
				srcs/numeric/ft_min_float.c			\

# string
SRCS		+=	srcs/string/ft_is_from_charset.c	\
				srcs/string/ft_strlen.c				\
				srcs/string/ft_strdup.c				\
				srcs/string/ft_strndup.c			\
				srcs/string/ft_strcpy.c				\
				srcs/string/ft_strlcpy.c			\
				srcs/string/ft_strcat.c				\
				srcs/string/ft_strlcat.c			\
				srcs/string/ft_strcmp.c				\
				srcs/string/ft_strncmp_rev.c		\
				srcs/string/ft_strncmp.c			\
				srcs/string/ft_strchr.c				\
				srcs/string/ft_strrchr.c			\
				srcs/string/ft_strmap.c				\
				srcs/string/ft_strmapi.c			\
				srcs/string/ft_substr.c				\
				srcs/string/ft_split_set.c			\
				srcs/string/ft_strjoin.c			\
				srcs/string/ft_strjoin_sep.c		\
				srcs/string/ft_strjoin_free.c		\
				srcs/string/ft_strtrim.c			\
				srcs/string/ft_strstr.c				\
				srcs/string/ft_strnstr.c			\
				srcs/string/ft_isprint.c			\
				srcs/string/ft_isalpha.c			\
				srcs/string/ft_isdigit.c			\
				srcs/string/ft_issign.c				\
				srcs/string/ft_isalnum.c			\
				srcs/string/ft_isascii.c			\
				srcs/string/ft_toupper.c			\
				srcs/string/ft_tolower.c			\
				srcs/string/ft_split.c				\


# ft_printf
SRCS 		+= 	srcs/ft_printf/ft_printf.c			\
				srcs/ft_printf/ft_s_printf_utils.c	\
				srcs/ft_printf/ft_char.c			\
				srcs/ft_printf/ft_hex.c				\
				srcs/ft_printf/ft_integer.c			\
				srcs/ft_printf/ft_integer2.c		\
				srcs/ft_printf/ft_pointer.c			\
				srcs/ft_printf/ft_string.c			\
				srcs/ft_printf/ft_unsigned_int.c	\
				srcs/ft_printf/ft_percent.c			\
				srcs/ft_printf/ft_width.c			\
				srcs/ft_printf/ft_flags.c			\
				srcs/ft_printf/ft_atoi_no_sign.c	\

SRCS		+=	srcs/gnl/get_next_line.c



###########################
BLACK_FG = \033[38;5;0m
RED_FG = \033[38;5;196m
GREEN_FG = \033[38;5;46m

BLACK_BG = \033[48;5;0m
BLUE_BG = \033[48;5;39m
PINK_BG = \033[48;5;213m
YELLOW_BG = \033[48;5;11m
RANLIB_BG = \033[48;5;172m

CLEAR_COLOR = \033[m
###########################

OPTI = -Ofast #-O3

all:		$(NAME)

$(NAME):	${OBJS} $(HEADER)
	@echo "Creating $(GREEN_FG)libft.a$(CLEAR_COLOR)"
	ar rc	$(NAME) ${OBJS}
	ranlib	$(NAME)

.c.o:
	${CC} -c ${CFLAGS} -I. -o $@ $<

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all
