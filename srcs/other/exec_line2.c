/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:04 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/16 10:54:56 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	fusion_cmd(t_list_cmd *cmd)
{
	while (cmd)
	{
		while (cmd->flags & F_NO_SP_AFTER && cmd->next &&
				!(cmd->next->flags & F_SPECIALS))
		{
			if (!(cmd->next->flags & F_NO_SP_AFTER))
				cmd->flags -= F_NO_SP_AFTER;
			cmd->str = ft_strjoin_free(cmd->str, cmd->next->str);
			cmd->flags = cmd->flags | cmd->next->flags;
			c_lst_remove_next_one(cmd);
		}
		cmd = cmd->next;
	}
}

t_list_cmd	*split_add_back(t_list_cmd *cmd, void (*del)(t_list_cmd *),\
				t_list_cmd *to_del)
{
	t_list_cmd	*next;
	int			flags;
	char		**tab;
	int			i;

	next = cmd->next;
	flags = cmd->flags - F_VAR_ENV;
	tab = ft_split_set(cmd->str, WSP);
	del(to_del);
	cmd = NULL;
	i = 0;
	if (!tab[i])
		c_lst_add_back(&cmd, c_lst_new("", F_VAR_PARSED + flags));
	while (tab[i])
		c_lst_add_back(&cmd, c_lst_new(tab[i++], F_VAR_PARSED + flags));
	c_lst_add_back(&cmd, next);
	ft_free_tab(tab);
	return (cmd);
}

t_list_cmd	*reparse_var_env(t_list_cmd *cmd)
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

char		*exec_cmd(t_list_line *lst_line, t_list *env)
{
	if (!lst_line->cmd)
		return (NULL);
	else if (!ft_strcmp(lst_line->cmd->str, "echo"))
		return (ft_echo(lst_line->cmd->next));
	else if (!ft_strcmp(lst_line->cmd->str, "cd"))
		return (ft_cd(lst_line->cmd->next, env));
	else if (!ft_strcmp(lst_line->cmd->str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(lst_line->cmd->str, "export"))
		return (ft_export(lst_line->cmd->next, env));
	else if (!ft_strcmp(lst_line->cmd->str, "unset"))
		return (ft_unset(lst_line->cmd->next, env));
	else if (!ft_strcmp(lst_line->cmd->str, "env"))
		return (ft_env(env));
	else if (!ft_strcmp(lst_line->cmd->str, "exit"))
		return (ft_exit(lst_line, env));
	else if (!search_command(lst_line, env))
		not_found(lst_line, env);
	g_glob.pid = 0;
	return (NULL);
}

int			make_and_exec_cmd(t_list_line *lst_line, t_list *env)
{
	char	*ret;

	replace_all_var_env(lst_line->cmd, env);
	fusion_cmd(lst_line->cmd);
	lst_line->cmd = reparse_var_env(lst_line->cmd);
	if (delete_backslashes(lst_line->cmd, env))
		return (FAILURE);
	delete_empty_elements(&(lst_line->cmd));
	if (redirections(lst_line))
		return (FAILURE);
	if ((ret = exec_cmd(lst_line, env)))
	{
		ft_putstr(ret);
		free(ret);
	}
	if (lst_line->output > 2 && close(lst_line->output) < 0)
		ft_putstr_fd("error close output\n", STDERR);
	return (SUCCESS);
}
