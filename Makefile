# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 20:30:49 by hthomas           #+#    #+#              #
#    Updated: 2020/10/20 08:56:22 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

--MAKE = make
--CC = gcc
--CFLAGS += -Wall -Werror -Wextra
--LDFLAGS += -g3 -fsanitize=address

--SRCS =	srcs/commands1.c		\
			srcs/commands2.c		\
			srcs/list_cmd1.c		\
			srcs/list_cmd2.c		\
			srcs/list_line1.c		\
			srcs/list_line2.c		\
			srcs/main.c				\
			srcs/parse.c			\
			srcs/parse_quotes.c		\
			srcs/search_command.c	\
			srcs/utils.c

--OBJS = $(--SRCS:.c=.o)
--INCL = includes/
--HEADER = $(--INCL)minishell.h

--LIBFT = libft.a
--LIBFTDIR = libft
--LIBFTLINK = -L $(--LIBFTDIR) -lft


###########################ALL
all:		$(NAME)

$(NAME):	$(--LIBFTDIR)/$(--LIBFT) $(--HEADER) $(--OBJS)
	$(--CC) $(--LDFLAGS) -o $@ $(--OBJS) $(--LIBFTLINK)


###########################LIBS
$(--LIBFTDIR)/$(--LIBFT):
	$(--MAKE) -C libft


###########################OBJECTS
%.o:		%.c $(--HEADER)
	$(--CC) -c $(--LDFLAGS) -I $(--INCL) -o $@ $<


###########################CLEAN
clean:
	@#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) clean
	rm -f $(--OBJS)

fclean:
	@#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) fclean
	rm -f $(--OBJS)
	rm -f $(NAME) a.out

re:			fclean all

.PHONY:		clean fclean
#.SILENT:


###########################TEST
test:		$(NAME)
	./$<
