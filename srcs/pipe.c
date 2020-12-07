/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:38:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/06 15:40:05 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		create_pipe(t_list_line **lst_line, t_list *env)
{
	t_list_cmd	*cmd;

	// ft_putstr("start pipe\n");
	if (!(*lst_line)->pipe)
		return (SUCCESS);
	// ft_putstr("in pipe\n");
	int		fdpipe[2]; // Used to store two ends of first pipe

	if (pipe(fdpipe) == -1) //error
	{
		ft_putstr_fd("pipe: pipe failed\n", STDERR);
		return (FAILURE);
	}
	// do something ?
	g_glob.pid = fork();
	if (g_glob.pid < 0) //error
	{
		ft_putstr_fd("pipe: fork failed\n", STDERR);
		return (FAILURE);
	}
	else if (g_glob.pid > 0) //parent process
	{
		close(fdpipe[1]);
		char	*line;
		wait(NULL);
			// if (get_next_line(&line, fdpipe[0]) == -1)
			// 	return (FAILURE);
			// ft_printf("***|%s|\n", line);
			// free(line);
		*lst_line = (*lst_line)->next;
		(*lst_line)->input = fdpipe[0];
		dup2((*lst_line)->input, STDIN);
	}
	else // child process
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
