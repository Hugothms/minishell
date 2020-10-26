/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/26 11:07:09 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: command not found: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(0);
}

char	*exec_cmd(t_list_cmd *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else if (!ft_strcmp(cmd->str, "echo"))
		return (ft_echo(cmd->next));
	else if (!ft_strcmp(cmd->str, "cd"))
		return (ft_cd(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->str, "export"))
		return (ft_export(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "unset"))
		return (ft_unset(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "env"))
		return (ft_env(envp));
	else if (!ft_strcmp(cmd->str, "exit"))
		return (ft_exit(cmd->next));
	else if (search_command(cmd, envp))
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

void	create_pipes_and_semicolon(t_list_line *lst_line)
{
	//! todo
}

void	open_fd(t_list_line *lst_line, t_list_cmd *cmd)
{
	char	*filename;

	filename = cmd->next->str;
	// ft_printf("filename:%s\n", filename);
	// ft_printf("before:%d\n", start->output);
	if (!filename)
		ft_putstr_fd("pas de filename\n", STDERR); //! todo
	if (cmd->flags & F_INPUT)
	{
		// input = filename; //! todo
		dup2(lst_line->input, STDIN);
	}
	else if (cmd->flags & F_APPEND)
		lst_line->output = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->flags & F_OUTPUT)
		lst_line->output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->flags & F_OUTPUT)
		dup2(lst_line->output, STDOUT);
	// ft_printf("open:%d\n", start->output);
	if (lst_line->output < 0)
		ft_putstr_fd("error open\n", STDERR);
	c_lst_remove_next_one(cmd);
}

void	redirections(t_list_line *lst_line, char **envp)
{
	t_list_cmd	*cmd;
	t_list_cmd	*tmp;

	lst_line->output = STDOUT;
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

void	exec_line(t_list_line *lst_line, char **envp)
{
	char		*ret;
	t_list_line	*start;
	int			fd_outold;
	int			fd_inold;

	fd_outold = dup(STDOUT);
	fd_inold = dup(STDIN);
	start = lst_line;
	while (lst_line)
	{
		redirections(lst_line, envp);

		// ft_printf("\nexec_line number:%d\n",i);
		// char **tab = lst_to_strs(lst_line->cmd);
		// ft_printf("***********************************\n", 0);
		// ft_print_tabstr(tab);
		// ft_printf("***********flags:%d\n", lst_line->cmd->flags);
		// ft_free_tab(tab);

		// tab = lst_to_strs(lst_line->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->next->cmd->flags);
		// ft_free_tab(tab);

		// tab = lst_to_strs(lst_line->next->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->next->next->cmd->flags);
		// ft_free_tab(tab);

		// ft_printf("***********************************\n");

		if ((ret = exec_cmd(lst_line->cmd, envp)))
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

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	t_list_line	*lst_line;

	ft_putstr(WELCOME_MSG);
	while (1)
	{
		print_prompt();
		get_next_line(&input, 0);
		lst_line = NULL;
		if (parse_input(input, &lst_line, envp))
		{
			parse_error(input, lst_line);
			continue ;
		}
		create_pipes_and_semicolon(lst_line);
		exec_line(lst_line, envp);
		free(input);
	}
	return (0);
}
