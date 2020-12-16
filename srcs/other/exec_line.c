/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:04 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/16 10:53:48 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		init_exec(int *fd_outold, int *fd_inold,
t_list_line **start, t_list_line **lst_line)
{
	*fd_outold = dup(STDOUT);
	*fd_inold = dup(STDIN);
	*start = *lst_line;
}

static void		reset_fds(int fd_outold, int fd_inold)
{
	dup2(fd_outold, STDOUT);
	dup2(fd_inold, STDIN);
}

static void		wait_all(int nb_wait)
{
	while (nb_wait--)
		if (wait(&g_glob.exit) == g_glob.pid)
			g_glob.exit = WEXITSTATUS(g_glob.exit);
}

static int		function(t_list_line *lst_line, t_list *env, int fd_outold,
int fd_inold)
{
	if (make_and_exec_cmd(lst_line, env))
	{
		reset_fds(fd_outold, fd_inold);
		return (FAILURE);
	}
	return (SUCCESS);
}

void			exec_line(t_list_line *lst_line, t_list *env)
{
	t_list_line	*start;
	int			nb_wait;
	int			ret;
	int			fd_outold;
	int			fd_inold;

	nb_wait = 0;
	init_exec(&fd_outold, &fd_inold, &start, &lst_line);
	while (lst_line)
	{
		while (lst_line && lst_line->pipe)
		{
			if ((ret = create_pipe(&lst_line, env, fd_inold, &nb_wait)) == 42)
				return (l_lst_clear(start));
			else if (ret)
				break ;
		}
		if (function(lst_line, env, fd_outold, fd_inold))
			break ;
		reset_fds(fd_outold, fd_inold);
		lst_line = lst_line->next;
	}
	wait_all(nb_wait);
	l_lst_clear(start);
}
