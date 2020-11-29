/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:33:37 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/27 18:11:16 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include "../libft/includes/libft.h"
# include "welcome_message.h"

/*
** Charsets
*/
# define WSP			" \t"
# define SYMBOLS		"|;<>"

// # define AFTER_VAR_ENV	"\t !\"#$%&'*+-./=:@[\\]^{}"

/*
** Error codes
*/
# define SUCCESS		0
# define FAILURE		-1

/*
** Exit codes
*/
# define CMD_NOT_FOUND	127
# define SYNTAX_ERROR	1

/*
** STD IN/OUT
*/
# define STDIN			0
# define STDOUT			1
# define STDERR			2

/*
** Flags cmd
*/
# define F_NOTHING		0
# define F_SIMPLE_QUOTE	1
# define F_DOUBLE_QUOTE	2
# define F_NO_SP_AFTER	4
# define F_SEMICOLON	8
# define F_PIPE			16
# define F_INPUT		32
# define F_OUTPUT		64
# define F_APPEND		128
# define F_REDIRS		F_INPUT + F_OUTPUT + F_APPEND
# define F_SPECIALS		F_REDIRS + F_SEMICOLON +F_PIPE
# define F_VAR_ENV		256
# define F_VAR_PARSED	512

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
	int					pipe;
	struct s_list_line	*next;
}						t_list_line;

typedef struct			s_parse
{
	int					in_simple;
	int					in_double;
	int					pos;
	int					i;
}						t_parse;

typedef struct			s_glob
{
	char				*path;
	pid_t				pid;
	int					exit;
}						t_glob;

t_glob	g_glob;

/*
** commands.c
*/
char					*ft_echo(t_list_cmd *args);
char					*ft_cd(t_list_cmd *args, t_list *env);
char					*ft_pwd();
char					*ft_export(t_list_cmd *args, t_list *env);
void					add_quote(char **tri);
void					sort(char **tri);
int						have_egual(char *str);
char					*ft_unset(t_list_cmd *args, t_list *env);
char					*ft_env(t_list *env);
char					*ft_exit(t_list_cmd *args, t_list *env);
char					*find_var_env(t_list *env, char *var);

/*
** exec_line.c
*/
int						make_and_exec_cmd(t_list_line *lst_line, t_list *env);
void					exec_line(t_list_line *lst_line, t_list *env);

/*
** parse.c
*/
int						delete_backslashes(t_list_cmd *cmd, t_list *env);
int						split_cmd(t_list_line **lst_line, t_list_cmd *cmd, int i);
void					delete_empty_elements(t_list_cmd **cmd);
int						parse_input(char *line, t_list_line **cmd, t_list *env);

/*
** parse_quotes.c
*/
int						input_to_command(char *input, t_list_cmd **cmd);

/*
** print.c
*/
void					print_prompt(void);
void					not_found(char *cmd);
void					parse_error(char *input, t_list_line *lst_line);

/*
** search_command.c
*/
int						search_command(t_list_cmd *cmd, t_list *env);

/*
** utils.c
*/
void					init_par(t_parse *par);
void					add_cmd(char *input, t_list_cmd **cmd,\
						int size, int flags);
int						escaped(char *str, int i);
int						in_quotes(t_list_cmd *cmd);
int						is_separator(char *str, int i);
int						get_flags(char *str);
void					cmd_plusplus_free(t_list_cmd **cmd);
char					**cmd_to_strs(t_list_cmd *cmd);
char					**lst_to_chartab(t_list *env);
void					err_code(t_list_cmd *cmd, t_list *env, int i);
void					modif_var_env(t_list *env, char *key, char *new_value);
void					clear_env_lst(t_list *env);

/*
** pipe.c
*/
int						create_pipe(t_list_line **lst_line, t_list *env);

/*
** redirection.c
*/
int						redirections(t_list_line *lst_line);

/*
** var_env.c
*/
void					replace_all_var_env(t_list_cmd *cmd, t_list *env);

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
