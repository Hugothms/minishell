/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/10 18:24:06 by hthomas          ###   ########.fr       */
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

// Charsets
# define WHITESPACES		" \t"
# define SEPARATORS			"|><;"

// Error codes
# define ERR				-1
# define OK					0

// Flags
# define F_NOTHING			0b0000
# define F_SIMPLE_QUOTES	0b0001
# define F_DOUBLE_QUOTES	0b0010
# define F_NO_SPACE_AFTER	0b0100
# define F_SEPARATOR		0b1000


// STRUCTURES
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



//commands.c
char	*ft_echo(t_list_cmd *args);
char	*ft_cd(t_list_cmd *args, char **envp);
char	*ft_pwd(void);
char	*ft_export(t_list_cmd *args, char **envp);
char	*ft_unset(t_list_cmd *args, char **envp);
char	*ft_env(t_list_cmd *args, char **envp);
char	*ft_exit(t_list_cmd *args);
char	*find_var_env(char **envp, char *var);


//parse.c
int		parse_input(char *line, t_list_line **cmd, char **envp);

//parse_quotes.c
void	simple_quotes(char *input, t_list_cmd **cmd, t_parse *par);
void	double_quotes(char *input, t_list_cmd **cmd, t_parse *par);
void	end_word(char *input, t_list_cmd **cmd, t_parse *par);
void	init_par(t_parse *par);
void	separator(char *input, t_list_cmd **cmd, t_parse *par);

//search_command.c
int		search_command(t_list_cmd *cmd, char **envp);

//utils.c
int		escaped(char *str, int i);
int		in_quotes(t_list_cmd *cmd);
void	parse_error_exit(char *input);
int		is_separator(char *str);

//list_cmd.c
t_list_cmd		*c_lst_new(char *str, char type);
void			c_lst_add_front(t_list_cmd **alst, t_list_cmd *new);
void			c_lst_add_back(t_list_cmd **alst, t_list_cmd *new);
int				c_lst_size(t_list_cmd *lst);
t_list_cmd		*c_lst_last(t_list_cmd *lst);
void			c_lst_free_one(void *lst);
void			c_lst_remove_next_one(t_list_cmd *lst);
void			c_lst_del_one(t_list_cmd *lst);
void			c_lst_clear(t_list_cmd *lst);
void			c_lst_iter(t_list_cmd *lst, void (*f)(void *));
t_list_cmd		*c_lst_map(t_list_cmd *lst, void *(*f)(void *));


//list_line.c
t_list_line		*l_lst_new(t_list_cmd *cmd, char separator);
void			l_lst_add_front(t_list_line **alst, t_list_line *new);
void			l_lst_add_back(t_list_line **alst, t_list_line *new);
int				l_lst_size(t_list_line *lst);
t_list_line		*l_lst_last(t_list_line *lst);
void			l_lst_free_one(void *lst);
void			l_lst_remove_next_one(t_list_line *lst);
void			l_lst_del_one(t_list_line *lst);
void			l_lst_clear(t_list_line *lst);
void			l_lst_iter(t_list_line *lst, void (*f)(void *));
t_list_line		*l_lst_map(t_list_line *lst, void *(*f)(void *));









































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
