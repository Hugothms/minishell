# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 11:49:24 by hthomas           #+#    #+#              #
#    Updated: 2020/09/25 13:47:22 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft.a
OBJS		=	${SRCS:.c=.o}
HEADER		=	libft.h
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

# io
SRCS		=	io/ft_print_tabint.c			\
				io/ft_putnbr.c					\
				io/ft_putnbr_fd.c				\
				io/ft_putnbr_unsigned_fd.c		\
				io/ft_putnbr_unsigned.c			\
				io/ft_putchar.c					\
				io/ft_putchar_fd.c				\
				io/ft_putendl_fd.c				\
				io/ft_puthex.c					\
				io/ft_putpointer.c				\
				io/ft_putstrn_fd.c				\
				io/ft_putstr_fd.c				\
				io/ft_putstr.c					\
				io/ft_putstrn.c					\
				io/ft_print_tabstr.c			\


# linked-list
SRCS		+=	linked-list/ft_lstnew.c				\
				linked-list/ft_lstadd_front.c		\
				linked-list/ft_lstsize.c			\
				linked-list/ft_lstlast.c			\
				linked-list/ft_lstadd_back.c		\
				linked-list/ft_lstdelone.c			\
				linked-list/ft_lstclear.c			\
				linked-list/ft_lstiter.c			\
				linked-list/ft_lstmap.c				\

# memory
SRCS		+=	memory/ft_swap.c					\
				memory/ft_memset.c					\
				memory/ft_memcpy.c					\
				memory/ft_memccpy.c					\
				memory/ft_memmove.c					\
				memory/ft_memchr.c					\
				memory/ft_memcmp.c					\
				memory/ft_calloc.c					\
				memory/ft_bzero.c					\
				memory/ft_chardup.c					\
				memory/ft_free_tab.c				\

# numeric
SRCS		+=	numeric/ft_nbrlen.c				\
				numeric/ft_convert_base.c		\
				numeric/ft_itoa.c				\
				numeric/ft_atol.c				\
				numeric/ft_uitoa.c				\
				numeric/ft_ltoa.c				\
				numeric/ft_ltoa_base.c			\
				numeric/ft_uitoa_base.c			\
				numeric/ft_itoa_width.c			\
				numeric/ft_pow.c				\
				numeric/ft_atoi.c				\
				numeric/ft_atoi_strict.c		\
				numeric/ft_atof.c				\
				numeric/ft_atoi_base.c			\
				numeric/ft_max_int.c			\
				numeric/ft_max_float.c			\
				numeric/ft_min_int.c			\
				numeric/ft_min_float.c			\

# string
SRCS		+=	string/ft_is_from_charset.c		\
				string/ft_strlen.c				\
				string/ft_strdup.c				\
				string/ft_strndup.c				\
				string/ft_strcpy.c				\
				string/ft_strlcpy.c				\
				string/ft_strcat.c				\
				string/ft_strlcat.c				\
				string/ft_strcmp.c				\
				string/ft_strncmp_rev.c			\
				string/ft_strncmp.c				\
				string/ft_strchr.c				\
				string/ft_strrchr.c				\
				string/ft_strmap.c				\
				string/ft_strmapi.c				\
				string/ft_substr.c				\
				string/ft_split_set.c			\
				string/ft_strjoin.c				\
				string/ft_strjoin_sep.c			\
				string/ft_strjoin_free.c		\
				string/ft_strtrim.c				\
				string/ft_strstr.c				\
				string/ft_strnstr.c				\
				string/ft_isprint.c				\
				string/ft_isalpha.c				\
				string/ft_isdigit.c				\
				string/ft_issign.c				\
				string/ft_isalnum.c				\
				string/ft_isascii.c				\
				string/ft_toupper.c				\
				string/ft_tolower.c				\
				string/ft_split.c


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
