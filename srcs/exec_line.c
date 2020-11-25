/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:04 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/25 11:37:59 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exec_cmd(t_list_cmd *cmd, t_list *env)
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

/*
** add flags together, for example 011 + 001 = 011 (and not 100 like addition)
*/

int 	bits_per_bits_or(int flags1, int flags2)
{
	int	sum;
	int	max;
	int	size;

	size = 0;
	max = ft_max_int(flags1, flags2);
	while (max)
	{
		max = max >> 1;
		size++;
	}
	sum = 0;
	while (size + 1)
	{
		sum += (flags1 >> size == 1 | flags2 >> size == 1) << size;
		size--;
	}
	return (sum);
}

void	fusion_cmd(t_list_cmd *cmd)
{
	while (cmd)
	{
		while (cmd->flags & F_NO_SP_AFTER && cmd->next && !(cmd->next->flags & F_SPECIALS))
		{
			if (!(cmd->next->flags & F_NO_SP_AFTER))
				cmd->flags -= F_NO_SP_AFTER;
			cmd->str = ft_strjoin_free(cmd->str, cmd->next->str);
			cmd->flags = bits_per_bits_or(cmd->flags, cmd->next->flags);
			c_lst_remove_next_one(cmd);
		}
		cmd = cmd->next;
	}
}

t_list_cmd	*split_add_back(t_list_cmd *cmd, void (*del)(t_list_cmd *), t_list_cmd *to_del)
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
		if (cmd->flags & F_VAR_ENV)
			cmd = split_add_back(cmd, c_lst_free_one, cmd);
		if (cmd->next && cmd->next->flags & F_VAR_ENV)
			cmd->next = split_add_back(cmd->next, c_lst_remove_next_one, cmd);
		if (!start)
			start = cmd;
		cmd = cmd->next;
	}
	return (start);
}

int		make_and_exec_cmd(t_list_line *lst_line, t_list *env, char **ret)
{
	replace_all_var_env(lst_line->cmd, env);
	fusion_cmd(lst_line->cmd);
	lst_line->cmd = reparse_var_env(lst_line->cmd);
	if (delete_backslashes(lst_line->cmd, env))
		return (FAILURE);
				// ft_printf("--------1--------\n");
				// t_list_cmd *copy = lst_line->cmd;
				// while (copy)
				// {
				// 	ft_printf("F:%d\t%s\n", copy->flags, copy->str);
				// 	copy = copy->next;
				// }
	if (redirections(lst_line))
		return (FAILURE);
	*ret = exec_cmd(lst_line->cmd, env);
	if (lst_line->output > 2 && close(lst_line->output) < 0)
		ft_putstr_fd("error close output\n", STDERR);
	if (lst_line->input > 2 && close(lst_line->input) < 0)
		ft_putstr_fd("error close input\n", STDERR);
	return (SUCCESS);
}

void	exec_line(t_list_line *lst_line, t_list *env)
{
	char		*ret;
	t_list_line	*start;

	int		fd_outold;
	int		fd_inold;
	fd_outold = dup(STDOUT);
	fd_inold = dup(STDIN);
	create_pipes_and_semicolon(lst_line, env);
	start = lst_line;
	while (lst_line)
	{
		if (make_and_exec_cmd(lst_line, env, &ret))
		{
			dup2(fd_outold, STDOUT);
			dup2(fd_inold, STDIN);
			break;
		}
		if (ret)
		{
			ft_putstr_fd(ret, 1/*lst_line->output*/);
			free(ret);
		}
		dup2(fd_outold, STDOUT);
		dup2(fd_inold, STDIN);
		lst_line = lst_line->next;
	}
	l_lst_clear(start);
}