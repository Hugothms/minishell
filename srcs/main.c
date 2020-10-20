/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/20 10:59:44 by hthomas          ###   ########.fr       */
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

void	exec_line(t_list_line *lst_line, char **envp)
{
	char		*ret;
	t_list_line	*start;
	int			fd_out;

	start = lst_line;
	// char ** tab = lst_to_strs(lst_line->cmd);
	// ft_print_tabstr(tab);
	// ft_putstr("===================\n");
	// ft_free_tab(tab);
	while (lst_line)
	{
		fd_out = STDOUT;
		if (lst_line->separator == '>' || lst_line->separator == '=')
		{
			char *filename = lst_line->next->cmd->str;
			if (!filename)
				ft_putstr_fd("pas de filename\n", STDERR);
			if (lst_line->separator == '<')
				fd_out = open(filename, O_RDONLY);
			else if (lst_line->separator == '>')
				fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (lst_line->separator == '=')
				fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out < 0)
				ft_putstr_fd("error open\n", STDERR);
			t_list_cmd *tmp = lst_line->next->cmd->next;
			lst_line->next->cmd = tmp;
			c_lst_del_one(tmp);
		}
		if ((ret = exec_cmd(lst_line->cmd, envp)))
		{
			ft_putstr_fd(ret, fd_out);
			free(ret);
		}
		if (fd_out > 2 && close(fd_out) < 0)
			ft_putstr_fd("error close\n", STDERR);
		lst_line = lst_line->next;
	}
	l_lst_clear(start);
}

void	in_developement_by_hugo(t_list_line *lst_line, char **envp)
{
	char		*ret;
	t_list_line	*start;

	start = lst_line;
	// char ** tab = lst_to_strs(lst_line->cmd);
	// ft_print_tabstr(tab);
	// ft_putstr("===================\n");
	// ft_free_tab(tab);
	while (lst_line)
	{
		int	fd_out;
		int	fd_in;
		int	oldfd;
		fd_out = STDOUT;
		if (lst_line->separator == '<' || lst_line->separator == '>' || lst_line->separator == '=')
		{

			char *filename = lst_line->next->cmd->str;
			if (!filename)
				ft_putstr_fd("pas de filename\n", STDERR);
			if (lst_line->separator == '<')
			{
				fd_in = open(filename, O_RDONLY);
				oldfd = dup(STDIN);
				dup2(fd_in, STDIN);

			}
			else if (lst_line->separator == '>')
			{
				fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				oldfd = dup(STDOUT);
				dup2(fd_out, STDOUT);
			}
			else if (lst_line->separator == '=')
			{
				fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				oldfd = dup(STDOUT);
				dup2(fd_out, STDOUT);
			}
			if (fd_out < 0)
				ft_putstr_fd("error open\n", STDERR);
			t_list_cmd *tmp = lst_line->next->cmd->next;
			lst_line->next->cmd = tmp;
			c_lst_del_one(tmp);
		}
		if ((ret = exec_cmd(lst_line->cmd, envp)))
		{
			ft_putstr_fd(ret, STDOUT);
			free(ret);
		}
		dup2(oldfd, STDOUT);
		if (fd_out > 2 && close(fd_out) < 0)
			ft_putstr_fd("error close\n", STDERR);
		lst_line = lst_line->next;
	}
	l_lst_clear(start);
			// int		tab[2];	// Used to store two ends of first pipe
			// pid_t	p;

			// if (pipe(tab) == -1)
			// {
			// 	ft_putstr_fd("Pipe Failed", STDERR);
			// 	return ;
			// }
			// //do something
			// p = fork();

			// if (p < 0)
			// {
			// 	ft_putstr_fd("fork Failed", STDERR);
			// 	return ;
			// }


			// // Parent process
			// else if (p > 0)
			// {

			// }
			// // Child process
			// else
			// {
			// 	dup2(fd_out, STDOUT);
			// }
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
			parse_error(input, lst_line);
		else
			in_developement_by_hugo(lst_line, envp);
		free(input);
	}
	return (0);
}
