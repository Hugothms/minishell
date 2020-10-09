/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 12:12:09 by hthomas          ###   ########.fr       */
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

# define WHITESPACES	" \t"


# define ERR			-1
# define OK				0

# define NOTHING		0b0000
# define SIMPLE_QUOTES	0b0001
# define DOUBLE_QUOTES	0b0010
# define NO_SPACE_AFTER	0b0100
# define idk				0b1000

typedef struct			s_list_cmd
{
	char				*str;
	int					flags;
	struct s_list_cmd	*next;
}						 t_list_cmd;

typedef struct			s_list_line
{
	t_list_cmd			*cmd;
	int					separator;
	struct s_list_line	*next;
}						 t_list_line;

typedef struct			s_parse
{
	int					in_simple;
	int					in_double;
	int					pos;
	int					i;
}						t_parse;



//commands
char	*ft_echo(t_list_cmd *args);
char	*ft_cd(t_list_cmd *args, char **envp);
char	*ft_pwd(void);
char	*ft_export(t_list_cmd *args, char **envp);
char	*ft_unset(t_list_cmd *args, char **envp);
char	*ft_env(t_list_cmd *args, char **envp);
char	*ft_exit(t_list_cmd *args);
char	*find_var_env(char **envp, char *var);


//parse
int		parse_input(char *line, t_list_cmd **cmd, char **envp);

//parse_quotes
void	simple_quotes(char *input, t_list_cmd **cmd, t_parse *par);
void	double_quotes(char *input, t_list_cmd **cmd, t_parse *par);
void	end_word(char *input, t_list_cmd **cmd, t_parse *par);
void	init_par(t_parse *par);

//search_command
int		search_command(t_list_cmd *cmd, char **envp);

//utils
int		escaped(char *str, int i);
int		in_quotes(t_list_cmd *cmd);
void	parse_error_exit(char *input);

//cmd_list
t_list_cmd		*c_lst_new(char *str, char type);
void			c_lst_add_front(t_list_cmd **alst, t_list_cmd *new);
void			c_lst_add_back(t_list_cmd **alst, t_list_cmd *new);
int				c_lst_size(t_list_cmd *lst);
t_list_cmd		*c_lst_last(t_list_cmd *lst);
void			c_lst_free_one(void *lst);
void			c_lst_remove_next_one(t_list_cmd *lst, void (*del)(void*));
void			c_lst_del_one(t_list_cmd *lst, void (*del)(void*));
void			c_lst_clear(t_list_cmd **alst, void (*del)(void*));
void			c_lst_iter(t_list_cmd *lst, void (*f)(void *));
t_list_cmd		*c_lst_map(t_list_cmd *lst, void *(*f)(void *), void (*del)(void *));


//line_list
t_list_line		*l_lst_new(t_list_cmd *cmd, char separator);
void			l_lst_add_front(t_list_line **alst, t_list_line *new);
void			l_lst_add_back(t_list_line **alst, t_list_line *new);
int				l_lst_size(t_list_line *lst);
t_list_line		*l_lst_last(t_list_line *lst);
void			l_lst_free_one(void *lst);
void			l_lst_remove_next_one(t_list_line *lst, void (*del)(void*));
void			l_lst_del_one(t_list_line *lst, void (*del)(void*));
void			l_lst_clear(t_list_line **alst, void (*del)(void*));
void			l_lst_iter(t_list_line *lst, void (*f)(void *));
t_list_line		*l_lst_map(t_list_line *lst, void *(*f)(void *), void (*del)(void *));









































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
