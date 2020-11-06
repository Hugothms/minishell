/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/06 14:08:41 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: command not found: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(CMD_NOT_FOUND);
}

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
	else if (search_command(cmd, env))
		not_found(cmd->str);
	return (NULL);
}

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr_fd("\xE2\x9E\xA1 ", STDOUT);
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, STDOUT);
	free(pwd);
	ft_putstr_fd("$ ", STDOUT);
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

void	fusion_cmd(t_list_cmd *cmd)
{
	while (cmd)
	{
		while (cmd->flags & F_NO_SP_AFTER && cmd->next && !(cmd->next->flags & F_SPECIALS))
		{
			if (!(cmd->next->flags & F_NO_SP_AFTER))
				cmd->flags -= F_NO_SP_AFTER;
			cmd->str = ft_strjoin_free(cmd->str, cmd->next->str);
			c_lst_remove_next_one(cmd);
		}
		cmd = cmd->next;
	}
}

void	exec_line(t_list_line *lst_line, t_list *env)
{
	char		*ret;
	t_list_line	*start;

	int		fd_outold;
	int		fd_inold;
	fd_outold = dup(STDOUT);
	fd_inold = dup(STDIN);
	create_pipes_and_semicolon(lst_line, env);
	// ft_printf("END PIPES\n");
	start = lst_line;
	while (lst_line)
	{
		replace_all_var_env(lst_line->cmd, env);
		fusion_cmd(lst_line->cmd);
		redirections(lst_line);

		// char **fdpipe = lst_to_strs(lst_line->cmd);
		// ft_printf("****************\n", 0);
		// ft_print_fdpipestr(fdpipe);
		// ft_printf("****************flags:%d\n", lst_line->cmd->flags);
		// ft_printf("*********************************************\n", 0);
		// ft_free_fdpipe(fdpipe);

		// fdpipe = lst_to_strs(lst_line->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_fdpipestr(fdpipe);
		// ft_printf("**************************%d\n", lst_line->next->cmd->flags);
		// ft_free_fdpipe(fdpipe);

		// fdpipe = lst_to_strs(lst_line->next->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_fdpipestr(fdpipe);
		// ft_printf("**************************%d\n", lst_line->next->next->cmd->flags);
		// ft_free_fdpipe(fdpipe);

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

void	set_env(char **envp, t_list **env)
{
	int		i;
	char	*keyval;

	i = 0;
	*env = NULL;
	while (envp[i])
	{
		keyval = ft_strdup(envp[i]);
		ft_lstadd_back(env, ft_lstnew(keyval));
		i++;
	}
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
	c_lst_add_back(&args, c_lst_new(tmp, F_NOTHING));
	free(tmp);
	tmp = ft_export(args, env);
	free(tmp);
	c_lst_clear(args);
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
	set_env(envp, &env);
	ft_putstr(WELCOME_MSG);
	increment_shlvl(env);
	while (1)
	{
		print_prompt();
		get_next_line(&input, 0);
		lst_line = NULL;
		if (parse_input(input, &lst_line, env))
		{
			parse_error(input, lst_line);
			continue;
		}
		exec_line(lst_line, env);
		free(input);
	}
	return (SUCCESS);
}
