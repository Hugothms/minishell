/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/30 14:04:20 by vmoreau          ###   ########.fr       */
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
# include "../libft/header/libft.h"



typedef struct	s_execve
{
	char	**argv;
	char	**envp;
}				t_execve;


//commands
char	*ft_echo(char **args);
char	*ft_cd(char **args, char **envp);
char	*ft_pwd(void);
char	*ft_export(char **args, char **envp);
char	*ft_unset(char **args, char **envp);
char	*ft_env(char **args, char **envp);
char	*ft_exit(char **args);

//parse
int		parse_input(char *line, char ***args);

//search_command
int		search_command(char **command, char **envp, t_execve exec);

//utils
void	ft_putstr_clean(char *str);











































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
