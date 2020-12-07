/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:38:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 15:06:18 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipe2(int fdpipe[2], t_list_line **lst_line, t_list *env)
{
	if (g_glob.pid > 0)
	{
		close(fdpipe[1]);
		wait(NULL);
		*lst_line = (*lst_line)->next;
		(*lst_line)->input = fdpipe[0];
		dup2((*lst_line)->input, STDIN);
	}
	else
	{
		close(fdpipe[0]);
		(*lst_line)->output = fdpipe[1];
		dup2((*lst_line)->output, STDOUT);
		if (make_and_exec_cmd((*lst_line), env))
			g_glob.exit = CMD_NOT_FOUND;
		close(fdpipe[1]);
		exit(0);
	}
}

int		create_pipe(t_list_line **lst_line, t_list *env)
{
	t_list_cmd	*cmd;
	int			fdpipe[2];

	if (!(*lst_line)->pipe)
		return (SUCCESS);
	if (pipe(fdpipe) == -1)
	{
		ft_putstr_fd("pipe: pipe failed\n", STDERR);
		return (FAILURE);
	}
	g_glob.pid = fork();
	if (g_glob.pid < 0)
	{
		ft_putstr_fd("pipe: fork failed\n", STDERR);
		return (FAILURE);
	}
	else
		create_pipe2(fdpipe, lst_line, env);
	return (SUCCESS);
}
