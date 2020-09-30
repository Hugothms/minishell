# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 15:18:39 by vmoreau           #+#    #+#              #
#    Updated: 2020/04/08 18:23:44 by vmoreau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

####################################COLOR######################################
#----------------reset----------------#
NC = \033[0m

#-----------Regular Colors------------#
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[35m
CYAN = \033[1;36m
WHITE = \033[0;37m

#####################################PATH######################################
MEM = src/memory/
CHAR = src/char/
STR = src/string/
OP = src/output/
CONV = src/conversion/
LST = src/list/
GNL = src/gnl/
PTF = src/printf/
####################################SOURCES####################################

#----------------CHAR----------------#
SRCS += $(CHAR)ft_isascii.c		$(CHAR)ft_isdigit.c $(CHAR)ft_isprint.c	\
		$(CHAR)ft_isalnum.c		$(CHAR)ft_isalpha.c $(CHAR)ft_tolower.c	\
		$(CHAR)ft_toupper.c

#---------------STRING---------------#
SRCS += $(STR)ft_strlcat.c		$(STR)ft_strncmp.c	$(STR)ft_strcmp.c	\
		$(STR)ft_strchr.c		$(STR)ft_strlcpy.c	$(STR)ft_strlen.c	\
		$(STR)ft_strrchr.c		$(STR)ft_strnstr.c	$(STR)ft_strdup.c	\
		$(STR)ft_substr.c		$(STR)ft_strjoin.c	$(STR)ft_strtrim.c	\
		$(STR)ft_strmapi.c		$(STR)ft_split.c

#---------------OUTPUT---------------#
SRCS += $(OP)ft_putchar_fd.c	$(OP)ft_putstr_fd.c	$(OP)ft_putendl_fd.c \
		$(OP)ft_putnbr_fd.c		$(OP)ft_putnbr.c	$(OP)ft_putchar.c	\
		$(OP)ft_putstr.c

#-------------CONVERSION-------------#
SRCS += $(CONV)ft_atoi.c		$(CONV)ft_itoa.c

#---------------MEMORY---------------#
SRCS +=	$(MEM)ft_memset.c		$(MEM)ft_bzero.c	$(MEM)ft_memcpy.c	\
		$(MEM)ft_memccpy.c		$(MEM)ft_memcmp.c	$(MEM)ft_memchr.c	\
		$(MEM)ft_memmove.c		$(MEM)ft_calloc.c

#----------------LIST----------------#
SRCS += $(LST)ft_lstadd_back.c	$(LST)ft_lstmap.c	$(LST)ft_lstclear.c	\
		$(LST)ft_lstdelone.c	$(LST)ft_lstiter.c	$(LST)ft_lstsize.c	\
		$(LST)ft_lstadd_front.c	$(LST)ft_lstlast.c	$(LST)ft_lstnew.c

#------------GET NEXT LINE-----------#
SRCS += $(GNL)get_next_line.c	$(GNL)get_next_line_utils.c

#---------------PRINTF---------------#
SRCS +=	$(PTF)ft_printf.c		$(PTF)check_flags.c	$(PTF)find_size.c	\
		$(PTF)init_struct.c		$(PTF)itoas.c		$(PTF)print_s.c		\
		$(PTF)print_u.c			$(PTF)print_c.c		$(PTF)print_x.c		\
		$(PTF)print_p.c			$(PTF)print_di.c	$(PTF)print_0.c		\
		$(PTF)check_di.c		$(PTF)check_s.c		$(PTF)check_cper.c	\
		$(PTF)check_uxp.c		$(PTF)check_di_d.c	$(PTF)set_ret.c

####################################BASIC######################################

CFLAGS = -Wall -Wextra -Werror

CC = clang

INC = header/

HEADER = $(INC)libft.h

OBJ = $(SRCS:.c=.o)

#####################################RULE######################################

all : $(NAME)

$(NAME) : echoCL $(OBJ) echoOK echoCS echoAR
	ar rcs $@ $(OBJ)

$(OBJ) : %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	printf "$(CYAN)."

clean :	echoCLEAN
	$(RM) $(OBJ)

fclean : clean echoFCLEAN
	$(RM) $(NAME)

re : fclean all

####################################ECHO######################################

echoCL:
	echo "$(YELLOW)===> Compiling Libft$(NC)"
echoOK:
	echo "$(GREEN)OK$(NC)"
echoCS :
	echo "$(GREEN)===> Compilation Success$(NC)"
echoCLEAN :
	echo "$(PURPLE)===> Cleanning OBJ libft$(NC)"
echoFCLEAN :
	echo "$(PURPLE)===> Cleanning Libft.a$(NC)"
echoAR :
	echo "$(CYAN)===> Archiving Libft$(NC)"

.PHONY : all clean fclean re

.SILENT :
