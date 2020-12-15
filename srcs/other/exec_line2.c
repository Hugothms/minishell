/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:04 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/15 11:31:28 by vmoreau          ###   ########.fr       */
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
	if (ret = exec_cmd(lst_line, env))
	{
		ft_putstr(ret);
		free(ret);
	}
	if (lst_line->output > 2 && close(lst_line->output) < 0)
		ft_putstr_fd("error close output\n", STDERR);
	return (SUCCESS);
}
