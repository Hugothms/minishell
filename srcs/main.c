/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/21 12:11:24 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exec_cmd(t_list_cmd *cmd, t_list *env)
{
	if (!cmd)
		return (NULL);
	else if (!ft_strcmp(cmd->str, "echo"))
		return (ft_echo(cmd->next));
	else if (!ft_strcmp(cmd->str, "cd"))
		return (ft_cd(cmd->next, env));
	else if (!ft_strcmp(cmd->str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->str, "export"))
		return (ft_export(cmd->next, env));
	else if (!ft_strcmp(cmd->str, "unset"))
		return (ft_unset(cmd->next, env));
	else if (!ft_strcmp(cmd->str, "env"))
		return (ft_env(env));
	else if (!ft_strcmp(cmd->str, "exit"))
		return (ft_exit(cmd->next, env));
	else if (!search_command(cmd, env))
		not_found(cmd->str);
	return (NULL);
}

void	create_pipes_and_semicolon(t_list_line *lst_line, t_list *env)
{
	t_list_cmd	*cmd;
	char		*ret;
	t_list_line	*start;

	// while (lst_line)
	// {
	// 	if (lst_line->pipe)
	// 	{
	// 		int tmp = lst_line->output;
	// 		lst_line->output = lst_line->next->input;
	// 		lst_line->next->input = tmp;
	// 		ft_printf("output:%d\n", lst_line->output);
	// 		ft_printf("input:%d\n\n", lst_line->next->input);
	// 	}
	// 	lst_line = lst_line->next;
	// }

	start = lst_line;
	while (lst_line)
	{
		if (lst_line->pipe)
		{
			int		fdpipe[2]; // Used to store two ends of first pipe
			pid_t	p;

			if (pipe(fdpipe) == -1) //error
			{
				ft_putstr_fd("pipe: pipe failed\n", STDERR);
				return;
			}
			// do something ?
			p = fork();
			if (p < 0) //error
			{
				ft_putstr_fd("pipe: fork failed\n", STDERR);
				return;
			}
			else if (p > 0) //parent process
			{
				close(fdpipe[1]);
				char	*line;
				ft_printf("***Before child exits\n");
				wait(NULL);
				ft_printf("***After child exits\n");
				if(get_next_line(&line, fdpipe[0]))
					return ;
				ft_printf("***line:%s\n***end line\n", line);
				close(fdpipe[0]);
			}
			else // child process
			{
				close(fdpipe[0]);
				lst_line->output = fdpipe[1];
				if ((ret = exec_cmd(lst_line->cmd, env)))
				{
					write(fdpipe[1], ret, strlen(ret)+1);
					free(ret);
				}
				else
					g_glob.exit = 127;
				close(fdpipe[1]);
				ft_printf("***End child\n");
				exit(0);
			}
			lst_line = lst_line->next;
			break;
		}
		lst_line = lst_line->next;
	}
}

void	open_fd(t_list_line *lst_line, t_list_cmd *cmd)
{
	char	*filename;

	filename = cmd->next->str;
	if (!filename)
		ft_putstr_fd("pas de filename\n", STDERR); //! todo
	//else if (cmd->flags & F_INPUT)
	// input = filename; //! todo
	else if (cmd->flags & F_APPEND)
		lst_line->output = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->flags & F_OUTPUT)
		lst_line->output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->flags & F_INPUT)
		dup2(lst_line->input, STDIN);
	if (cmd->flags & F_OUTPUT)
		dup2(lst_line->output, STDOUT);
	if (lst_line->output < 0)
		ft_putstr_fd("error open\n", STDERR);
	c_lst_remove_next_one(cmd);
}

void	redirections(t_list_line *lst_line)
{
	t_list_cmd	*cmd;
	t_list_cmd	*tmp;

	cmd = lst_line->cmd;
	while (cmd)
	{
		while (cmd->flags & (F_OUTPUT + F_INPUT))
		{
			open_fd(lst_line, cmd);
			tmp = cmd;
			lst_line->cmd = cmd->next;
			cmd = lst_line->cmd;
			c_lst_free_one(tmp);
		}
		if (cmd->next && cmd->next->flags & (F_OUTPUT + F_INPUT))
		{
			open_fd(lst_line, cmd->next);
			tmp = cmd->next;
			cmd->next = cmd->next->next;
			c_lst_free_one(tmp);
		}
		cmd = cmd->next;
	}
}

int 	add_flags(int flags1, int flags2)
{
	int	sum;
	int	max;
	int	size;

	size = 0;
	max = ft_max_int(flags1, flags2);
	while (max)
	{
		max = max >> 1;
		size++;
	}
	sum = 0;
	while (size + 1)
	{
		sum += (flags1 >> size == 1 | flags2 >> size == 1) << size;
		size--;
	}
	return (sum);
}

void	fusion_cmd(t_list_cmd *cmd)
{
	while (cmd)
	{
		while (cmd->flags & F_NO_SP_AFTER && cmd->next && !(cmd->next->flags & F_SPECIALS))
		{
			if (!(cmd->next->flags & F_NO_SP_AFTER))
				cmd->flags -= F_NO_SP_AFTER;
			cmd->str = ft_strjoin_free(cmd->str, cmd->next->str);
			cmd->flags = add_flags(cmd->flags, cmd->next->flags);
			c_lst_remove_next_one(cmd);
		}
		cmd = cmd->next;
	}
}

t_list_cmd	*split_add_back(t_list_cmd *cmd,  void (*del)(t_list_cmd *), t_list_cmd *to_del)
{
	t_list_cmd	*next;
	char		**tab;
	int			i;

	next = cmd->next;
	tab = ft_split_set(cmd->str, WSP);
	del(to_del);
	cmd = NULL;
	i = 0;
	while (tab[i])
		c_lst_add_back(&cmd, c_lst_new(tab[i++], F_NOTHING));
	ft_free_tab(tab);
	c_lst_add_back(&cmd, next);
	return (cmd);
}

t_list_cmd	*reparse(t_list_cmd *cmd)
{
	t_list_cmd	*start;

	start = NULL;
	while (cmd)
	{
		if (cmd->flags & F_VAR_ENV)
			cmd = split_add_back(cmd, c_lst_free_one, cmd);
		if (cmd->next && cmd->next->flags & F_VAR_ENV)
			cmd->next = split_add_back(cmd->next, c_lst_remove_next_one, cmd);
		if (!start)
			start = cmd;
		cmd = cmd->next;
	}
	return (start);
}

// t_list_cmd	*reparse1(t_list_cmd *cmd)
// {
// 	t_list_cmd	*start;
// 	// t_list_cmd	*tmp;
// 	start = NULL;
// 	while (cmd)
// 	{
// 		if (cmd->flags & F_VAR_ENV) // or !(cmd->flags & F_DOUBLE_QUOTE && cmd->flags & F_DOUBLE_QUOTE)
// 		{
// 			t_list_cmd *next = cmd->next;
// 			char **tab = ft_split_set(cmd->str, WSP);
// 			c_lst_free_one(cmd);
// 			cmd = NULL;
// 			while (*tab)
// 				c_lst_add_back(&cmd, c_lst_new(*tab++, F_NOTHING));
// 			// tmp = NULL;
// 			// if (input_to_command(cmd->str, &tmp))
// 			// 	return (NULL);
// 			// c_lst_free_one(cmd);
// 			// cmd = tmp;
// 			c_lst_add_back(&cmd, next);
// 		}
// 		if (!start)
// 			start = cmd;
// 		cmd = cmd->next;
// 	}
// 	return (start);
// }

// t_list_cmd	*reparse2(t_list_cmd *cmd)
// {
// 	t_list_cmd	*start;
// 	t_list_cmd	*tmp;
// 	char		*str;
// 	start = NULL;
// 	while (cmd)
// 	{
// 		if (cmd->flags & F_VAR_ENV) // or !(cmd->flags & F_DOUBLE_QUOTE && cmd->flags & F_DOUBLE_QUOTE)
// 		{
// 			t_list_cmd *next = cmd->next;
// 			str = ft_strdup(cmd->str);
// 			tmp = NULL;
// 			if (input_to_command(str, &tmp))
// 				return (NULL);
// 			c_lst_free_one(cmd);
// 			cmd = tmp;
// 			c_lst_add_back(&cmd, next);
// 			free(str);
// 		}
// 		if (!start)
// 			start = cmd;
// 		cmd = cmd->next;
// 	}
// 	return (start);
// }

void	exec_line(t_list_line *lst_line, t_list *env)
{
	char		*ret;
	t_list_line	*start;

	int		fd_outold;
	int		fd_inold;
	fd_outold = dup(STDOUT);
	fd_inold = dup(STDIN);
	create_pipes_and_semicolon(lst_line, env);
	start = lst_line;
	while (lst_line)
	{
		// ft_printf("--------1--------\n");
		// t_list_cmd *copy = lst_line->cmd;
		// while (copy)
		// {
		// 	ft_printf("F:%d\t%s\n", copy->flags, copy->str);
		// 	copy = copy->next;
		// }
		replace_all_var_env(lst_line->cmd, env);
		fusion_cmd(lst_line->cmd);
		lst_line->cmd = reparse(lst_line->cmd);
		if (delete_backslashes(lst_line->cmd, env))
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR);
			return (l_lst_clear(start));
		}
		redirections(lst_line);


		// tab = cmd_to_strs(lst_line->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->next->cmd->flags);
		// ft_free_tab(tab);

		// tab = cmd_to_strs(lst_line->next->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->next->next->cmd->flags);
		// ft_free_tab(tab);

		// ft_printf("***********************************\n");

		if ((ret = exec_cmd(lst_line->cmd, env)))
		{
			ft_putstr_fd(ret, lst_line->output);
			free(ret);
		}
		if (lst_line->output > 2 && close(lst_line->output) < 0)
			ft_putstr_fd("error close\n", STDERR);
		dup2(fd_outold, STDOUT);
		dup2(fd_inold, STDIN);
		lst_line = lst_line->next;
	}
	l_lst_clear(start);
}

void	fill_env(t_list **env)
{
	char	*keyval;
	char	*pwd;

	keyval = ft_strdup("SHLVL=0");
	ft_lstadd_back(env, ft_lstnew(keyval));
	pwd = getcwd(NULL, 0);
	keyval = ft_strjoin("PWD=", pwd);
	free(pwd);
	ft_lstadd_back(env, ft_lstnew(keyval));
	keyval = ft_strdup("OLDPWD=");
	ft_lstadd_back(env, ft_lstnew(keyval));
}

void	set_env(char **envp, t_list **env)
{
	int		i;
	char	*keyval;

	i = 0;
	*env = NULL;
	if (envp[i])
	{
		while (envp[i])
		{
			keyval = ft_strdup(envp[i]);
			ft_lstadd_back(env, ft_lstnew(keyval));
			i++;
		}
	}
	else
		fill_env(env);
}

void	increment_shlvl(t_list *env)
{
	t_list_cmd	*args;
	char		*tmp;
	int			sh_lvl;

	args = c_lst_new("$SHLVL", F_VAR_ENV);
	replace_all_var_env(args, env);
	sh_lvl = ft_atoi(args->str);
	c_lst_clear(args);
	args = c_lst_new("SHLVL", F_NOTHING);
	tmp = ft_itoa(sh_lvl + 1);
	args->str = ft_strjoin_free(args->str, "=");
	args->str = ft_strjoin_free(args->str, tmp);
	free(tmp);
	tmp = ft_export(args, env);
	free(tmp);
	c_lst_clear(args);
}

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT);
		print_prompt();
		g_glob.exit = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT);
		print_prompt();
		g_glob.exit = 131;
	}
}

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	t_list_line	*lst_line;
	t_list		*env;

	if (argc != 1)
	{
		ft_putstr_fd("ERROR: Too many argument\n", STDERR);
		return (FAILURE);
	}
	g_glob.exit = 0;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	set_env(envp, &env);
	ft_putstr(WELCOME_MSG);
	increment_shlvl(env);
	print_prompt();
	while (get_next_line(&input, 0) > 0)
	{
		lst_line = NULL;
		if (parse_input(input, &lst_line, env))
		{
			parse_error(input, lst_line);
			continue;
		}
		exec_line(lst_line, env);
		free(input);
		print_prompt();
	}
	clear_env_lst(env);
	free(input);
	ft_printf("\n");
	return (g_glob.exit);
}
