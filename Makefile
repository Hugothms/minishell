# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 20:30:49 by hthomas           #+#    #+#              #
#    Updated: 2020/09/15 21:11:20 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell

--MAKE = make
--CC = gcc
--CFLAGS += -Wall -Werror -Wextra
--LDFLAGS += -g3 -fsanitize=address

--SRCS =	srcs/main.c	\
			srcs/get_next_line.c


--OBJS = $(--SRCS:.c=.o)
--INCL = includes/
--HEADER = $(--INCL)minishell.h

--LIBFT = libft.a
--LIBFTDIR = libft
--LIBFTLINK = -L $(--LIBFTDIR) -lft

--FTPRINTF = libftprintf.a
--FTPRINTFDIR = ft_printf
--FTPRINTFLINK = -L $(--FTPRINTFDIR) -lftprintf


###########################ALL
all : $(--LIBFTDIR)/$(--LIBFT) $(NAME)

$(NAME) : $(--OBJS) $(--HEADER) $(--LIBFTDIR)/$(--LIBFT)
	$(--CC) $(--LDFLAGS) -o $@ $(--OBJS) $(--LIBFTLINK)


###########################LIBS
$(--LIBFTDIR)/$(--LIBFT) :
	$(--MAKE) -C libft all

$(--FTPRINTFDIR)/$(--FTPRINTF) :
	$(--MAKE) -C $(--FTPRINTFDIR) all

%.o: %.c $(--HEADER)
	$(--CC) -c $(--LDFLAGS) -I $(--INCL) -o $@ $<

###########################CLEAN
clean:
	#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) clean
	# cd $(--LIBMLXDIR) && $(--MAKE) clean

fclean:		clean
	#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) fclean
	cd $(--FTPRINTFDIR) && $(--MAKE) fclean
	rm -f $(NAME) a.out

re:		fclean all

.PHONY: clean fclean

#.SILENT:

###########################TEST
test: $(NAME)
	./$< scenes/test.cub

