/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:04 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 18:41:22 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*exec_cmd(t_list_cmd *cmd, t_list *env)
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

t_list_cmd		*reparse_var_env(t_list_cmd *cmd)
{
	t_list_cmd	*start;

	start = NULL;
	while (cmd)
	{
		if (cmd->flags & F_VAR_ENV && !(cmd->flags & F_DOUBLE_QUOTE))
			cmd = split_add_back(cmd, c_lst_free_one, cmd);
		if (cmd->next && cmd->next->flags & F_VAR_ENV &&
				!(cmd->next->flags & F_DOUBLE_QUOTE))
			cmd->next = split_add_back(cmd->next, c_lst_remove_next_one, cmd);
		if (!start)
			start = cmd;
		cmd = cmd->next;
	}
	return (start);
}

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

void			exec_line(t_list_line *lst_line, t_list *env)
{
	char		*ret;
	t_list_line	*start;
	int			fd_outold;
	int			fd_inold;
	int			i;

	init_exec(&fd_outold, &fd_inold, &start, &lst_line);
	while (lst_line)
	{
		while (lst_line && lst_line->pipe)
		{
			if ((i = create_pipe(&lst_line, env, fd_inold)) == 42)
				return (l_lst_clear(start));
			else if (i)
				break ;
		}
		if (make_and_exec_cmd(lst_line, env))
		{
			reset_fds(fd_outold, fd_inold);
			break ;
		}
		reset_fds(fd_outold, fd_inold);
		lst_line = lst_line->next;
	}
	l_lst_clear(start);
}
