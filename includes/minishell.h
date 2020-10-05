/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 16:23:50 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_H
# define minishell_H

# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include "../libft/includes/libft.h"

# define WHITESPACES    " \t"

# define NOTHING        0
# define SIMPLE_QUOTES  0b0001
# define DOUBLE_QUOTES  0b0010
# define NO_SPACE_AFTER 0b0100
# define B              0b1000

typedef struct		s_list_command
{
	char					        *str;
	int					          flags;
	struct s_list_command	*next;
}					t_list_command;

typedef struct		s_parse
{
	int	in_simple;
	int	in_double;
	int	pos;
	int	i;
}			        		t_parse;



//commands
char	*ft_echo(t_list_command *args);
char	*ft_cd(t_list_command *args, char **envp);
char	*ft_pwd(void);
char	*ft_export(t_list_command *args, char **envp);
char	*ft_unset(t_list_command *args, char **envp);
char	*ft_env(t_list_command *args, char **envp);
char	*ft_exit(t_list_command *args);

//parse
int		parse_input(char *line, t_list_command **command, char **envp);

//parse_quotes
void	simple_quotes(char *input, t_list_command **command, t_parse *par);
void	double_quotes(char *input, t_list_command **command, t_parse *par);
void	end_word(char *input, t_list_command **command, t_parse *par);
void	init_par(t_parse *par);

//search_command
int		search_command(t_list_command *command, char **envp);

//utils
int		escaped(char *str, int i);

//linked_list
t_list_command  *c_lstnew(char *str, char type);
void	          c_lstadd_front(t_list_command **alst, t_list_command *new);
int	            c_lstsize(t_list_command *lst);
t_list_command  *c_lstlast(t_list_command *lst);
void	          c_lstadd_back(t_list_command **alst, t_list_command *new);
void	          c_lstdelone(t_list_command *lst, void (*del)(void*));
void	          c_lstclear(t_list_command **alst, void (*del)(void*));
void	          c_lstiter(t_list_command *lst, void (*f)(void *));
t_list_command  *c_lstmap(t_list_command *lst, void *(*f)(void *), void (*del)(void *));









































# define WELCOME_MSG "            ▄███████████████▄           \n\
         ██████▀   ██   ▀███████        \n\
      ███   ▀███   ██   ███▀   ███      \n\
     ██████   ██   ██   ██   ██████     \n\
     ██   ██   ██  ██  ██   ██   ██     \n\
    ███    ██  ██  ██  ██  ██    ███    \n\
    ██ ██   ██  █  ██  █  ██   ██ ██    \n\
    ██  ███  ██ ██ ██ ██ ██  ███  ██    \n\
    ██    ██  ██ █ ██ █ ██  ██    ██    \n\
    ████▄   ██ █  █  █  █  █   ▄████    \n\
       ████   █          █   ████       \n\
          ██                ██          \n\
          ████████▄  ▄████████          \n\
                  ▀██▀                  \n\
           _       _     _          _ _\n\
 _ __ ___ (_)_ __ (_)___| |__   ___| | |\n\
| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n\
| | | | | | | | | | \\__ \\ | | |  __/ | |\n\
|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n\n"


/*
                                \n\
        ▄███████████████▄       \n\
       ███████████████████      \n\
     ██████▀   ██   ▀███████    \n\
   ████████    ██    ████████   \n\
  ███   ▀███   ██   ███▀   ███  \n\
  ████    ██   ██   ██    ████  \n\
 ██████   ██   ██   ██   ██████ \n\
 ██  ██   ██   ██   ██   ██  ██ \n\
 ██   ██   ██  ██  ██   ██   ██ \n\
███   ██   ██  ██  ██   ██   ███\n\
███    ██  ██  ██  ██  ██    ███\n\
████   ██  ██  ██  █   ██   ████\n\
██ ██   ██  █  ██  █  ██   ██ ██\n\
██  ██  ██  ██ ██ ██  ██  ██  ██\n\
██  ███  ██ ██ ██ ██ ██  ███  ██\n\
██   ██  ██  █ ██ █  ██  ██   ██\n\
██    ██  ██ █ ██ █ ██  ██    ██\n\
███▄   ██  █ █ ██ █ █   █   ▄███\n\
████▄   ██ █  █  █  █  █   ▄████\n\
 █████   █  █ █  █ █  █   █████ \n\
   ████   █          █   ████   \n\
     ███                ███     \n\
      ██                ██      \n\
      ██                ██      \n\
      ████████▄  ▄████████      \n\
      ████████████████████      \n\
              ▀██▀              \n\
*/

#endif
