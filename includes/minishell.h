/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/26 11:16:52 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
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
# include "welcome_message.h"

/*
** Charsets
*/
# define WHITESPACES	" \t"
# define SYMBOLS		"|;<>"

/*
** Error codes
*/
# define SUCCESS		0
# define FAILURE		-1

/*
** STD IN/OUT
*/
# define STDIN			0
# define STDOUT			1
# define STDERR			2

/*
** Flags cmd
*/
# define F_NOTHING		0b00000000
# define F_SIMPLE_QUOTE	0b00000001
# define F_DOUBLE_QUOTE	0b00000010
# define F_NO_SP_AFTER	0b00000100

# define F_SEMICOLON	0b00001000
# define F_PIPE			0b00010000

# define F_INPUT		0b00100000
# define F_OUTPUT		0b01000000
# define F_APPEND		0b10000000

# define F_REDIRS		0b11100000
# define F_SPECIALS		0b11111000

typedef struct			s_list_cmd
{
	char				*str;
	int					flags;
	struct s_list_cmd	*next;
}						t_list_cmd;

typedef struct			s_list_line
{
	t_list_cmd			*cmd;
	int					input;
	int					output;
	struct s_list_line	*next;
}						t_list_line;

typedef struct			s_parse
{
	int					in_simple;
	int					in_double;
	int					pos;
	int					i;
}						t_parse;

/*
** commands.c
*/
char					*ft_echo(t_list_cmd *args);
char					*ft_cd(t_list_cmd *args, char **envp);
char					*ft_pwd(void);
char					*ft_export(t_list_cmd *args, char **envp);
char					*ft_unset(t_list_cmd *args, char **envp);
char					*ft_env(char **envp);
char					*ft_exit(t_list_cmd *args);
char					*find_var_env(char **envp, char *var);

/*
** parse.c
*/
int						parse_input(char *line, t_list_line **cmd, char **envp);

/*
** parse_quotes.c
*/
int						input_to_command(char *input, t_list_cmd **cmd);

/*
** search_command.c
*/
int						search_command(t_list_cmd *cmd, char **envp);

/*
** utils.c
*/
void					init_par(t_parse *par);
void					add_substr_to_cmd(char *input, t_list_cmd **cmd,\
						int size, int flags);
int						escaped(char *str, int i);
int						in_quotes(t_list_cmd *cmd);
void					parse_error(char *input, t_list_line *lst_line);
int						is_separator(char *str, int i);
int						get_flags(char *str);
void					cmd_plusplus_free(t_list_cmd **cmd);
char					**lst_to_strs(t_list_cmd *cmd);

/*
** list_cmd.c
*/
t_list_cmd				*c_lst_new(char *str, int flags);
void					c_lst_add_front(t_list_cmd **alst, t_list_cmd *new);
void					c_lst_add_back(t_list_cmd **alst, t_list_cmd *new);
int						c_lst_size(t_list_cmd *lst);
t_list_cmd				*c_lst_last(t_list_cmd *lst);
void					c_lst_free_one(t_list_cmd *lst);
void					c_lst_remove_next_one(t_list_cmd *lst);
void					c_lst_clear(t_list_cmd *lst);
void					c_lst_iter(t_list_cmd *lst, void (*f)(void *));
t_list_cmd				*c_lst_map(t_list_cmd *lst, void *(*f)(void *));

/*
** list_line.c
*/
t_list_line				*l_lst_new(t_list_cmd *cmd);
void					l_lst_add_front(t_list_line **alst, t_list_line *new);
void					l_lst_add_back(t_list_line **alst, t_list_line *new);
int						l_lst_size(t_list_line *lst);
t_list_line				*l_lst_last(t_list_line *lst);
void					l_lst_free_one(t_list_line *lst);
void					l_lst_remove_next_one(t_list_line *lst);
void					l_lst_clear(t_list_line *lst);
void					l_lst_iter(t_list_line *lst, void (*f)(void *));
t_list_line				*l_lst_map(t_list_line *lst, void *(*f)(void *));
t_list_line				*l_lst_copy_all(t_list_cmd *cmd);

#endif
