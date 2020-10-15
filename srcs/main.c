/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/15 21:55:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *cmd)
{
	char *ret;
	char *tmp;

	ret = ft_strjoin("minishell: command not found: ", cmd);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	free(tmp);
	ft_putstr(ret);
	free(ret);
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
		return (ft_env(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "exit"))
		return (ft_exit(cmd->next));
	else if (search_command(cmd, envp))
		not_found(cmd->str);
}

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr("\xE2\x9E\xA1 ");
	pwd = getcwd(NULL, 0);
	ft_putstr(pwd);
	free(pwd);
	ft_putstr(": ");
}

void	exec_line(t_list_line *lst_line, char **envp)
{
	char		*ret;
	t_list_line	*start;
	int			fd;

	start = lst_line;
	// char ** tab = lst_to_strs(lst_line->cmd);
	// ft_print_tabstr(tab);
	// ft_putstr("===================\n");
	// ft_free_tab(tab);
	while (lst_line)
	{
		fd = 1;
		if (lst_line->separator == '>' || lst_line->separator == '=')
		{
			char *filename = lst_line->next->cmd->str;
			if (!filename)
				ft_putstr("pas de filename\n");
			if (lst_line->separator == '>')
				fd = open(filename, O_WRONLY | O_CREAT, 777);
			else if (lst_line->separator == '=')
				fd = open(filename, O_APPEND | O_CREAT);
			if (fd < 0)
				ft_putstr("error open\n");
			t_list_cmd *tmp = lst_line->next->cmd->next;
			lst_line->next->cmd = tmp;
			c_lst_del_one(tmp);
		}
		if (ret = exec_cmd(lst_line->cmd, envp))
		{
			ft_putstr_fd(ret, fd);
			free(ret);
		}
		if (fd > 2 && close(fd) < 0)
			ft_putstr("error close\n");
		lst_line = lst_line->next; 
	}
	l_lst_clear(start);
}

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	t_list_line	*lst_line;

	ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while (1)
	{
		free(input);
		print_prompt();
		get_next_line(&input, 0);
		lst_line = NULL;
		if (parse_input(input, &lst_line, envp))
			parse_error(input, lst_line);
		else
			exec_line(lst_line, envp);
	}
	free(input);
	return (0);
}
