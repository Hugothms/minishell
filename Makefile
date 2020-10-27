# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 20:30:49 by hthomas           #+#    #+#              #
#    Updated: 2020/10/27 16:59:51 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS += -Wall -Werror -Wextra
LDFLAGS += #-g3 -fsanitize=address

#-----------------Main-----------------#

SRCS += srcs/main.c
#---------------Commands---------------#

SRCS +=	srcs/commands/ft_cd.c		\
		srcs/commands/ft_echo.c		\
		srcs/commands/ft_env.c		\
		srcs/commands/ft_exit.c		\
		srcs/commands/ft_export.c	\
		srcs/commands/ft_export2.c	\
		srcs/commands/ft_pwd.c		\
		srcs/commands/ft_unset.c

#----------------Others----------------#
SRCS +=	srcs/list_cmd1.c		\
		srcs/list_cmd2.c		\
		srcs/list_line1.c		\
		srcs/list_line2.c		\
		srcs/parse.c			\
		srcs/parse_quotes.c		\
		srcs/search_command.c	\
		srcs/utils.c

OBJS = $(SRCS:.c=.o)
INCL = includes/
HEADER = $(INCL)minishell.h

LIBFT = libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft


###########################ALL
all:		$(NAME)

$(NAME):	complib echoCL $(OBJS) echoOK echoCS
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBFTLINK)


###########################LIBS
complib:
	$(MAKE) -C libft/


###########################OBJECTS
%.o:		%.c $(HEADER)
	$(CC) -c $(LDFLAGS) -I $(INCL) -o $@ $<
	printf "$(GREEN)██"


###########################CLEAN
clean: echoCLEAN 
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(OBJS)

fclean: clean echoFCLEAN
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(OBJS)
	rm -f $(NAME) a.out

re:			fclean all

.PHONY:		clean fclean
.SILENT:

###########################COLOR
#----------------reset----------------#
NC = \033[0m

#-----------Regular Colors------------#
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[0;37m

###########################ECHO
echoCL:
	echo "$(YELLOW)===> Compiling $(RED)Minishell$(NC)\n"
echoOK:
	echo "$(GREEN) OK$(NC)\n"
echoCS :
	echo "$(GREEN)===> Compilation Success$(NC)\n"
echoCLEAN :
	echo "\n$(PURPLE)===> Cleanning OBJS$(NC)"
echoFCLEAN :
	echo "$(PURPLE)===> Cleanning Exec & Lib$(NC)\n"

###########################TEST
test:		$(NAME)
	./$<
