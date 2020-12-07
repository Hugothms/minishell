/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:38:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 18:24:49 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	last_pipe_exit(t_list_line **lst_line, int fd_inold)
{
	dup2(fd_inold, STDIN);
	l_lst_remove_next_one(*lst_line);
	*lst_line = (*lst_line)->next;
	return (42);
}

static int	create_pipe2(int fdpipe[2], t_list_line **lst_line, t_list *env,\
int fd_inold)
{
	if (g_glob.pid > 0)
	{
		close(fdpipe[1]);
		wait(NULL);
		if ((*lst_line)->pipe && !((*lst_line)->next->next) &&\
		!ft_strncmp((*lst_line)->next->cmd->str, "exit", 5))
			return (last_pipe_exit(lst_line, fd_inold));
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
	return (SUCCESS);
}

int			create_pipe(t_list_line **lst_line, t_list *env, int fd_inold)
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
		return (create_pipe2(fdpipe, lst_line, env, fd_inold));
}
