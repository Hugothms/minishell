/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 17:28:03 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		delete_backslashes(t_list_cmd *cmd, t_list *env)
{
	int		i;

	while (cmd)
	{
		i = 0;
		while (cmd->str && !(cmd->flags & F_SIMPLE_QUOTE) && cmd->str[i])
		{
			if (cmd->str[i] == '\\')
			{
				if (check_del_backslash(cmd, i) == 1)
				{
					i++;
					continue;
				}
				else if (cmd->str[i + 1])
					ft_strcpy(&cmd->str[i], &cmd->str[i + 1]);
				else if (cmd->flags != 512)
					return (print_synt_err());
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int		flag_dollar_and_replace_tild(t_list_cmd *cmd, t_list *env)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			if (cmd->str[i] == '$' && !escaped(cmd->str, i) &&\
				!(cmd->flags & F_SIMPLE_QUOTE) && cmd->str[i + 1] > 32 &&
				!(cmd->flags & F_VAR_ENV))
				cmd->flags += F_VAR_ENV;
			else if (cmd->str[i] == '~' && !escaped(cmd->str, i) &&\
			!in_quotes(cmd) && (!cmd->str[i + 1] || cmd->str[i + 1] == '/'))
			{
				tmp = cmd->str;
				cmd->str = ft_strdup(&find_var_env(env, "HOME=")[5]);
				free(tmp);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	split_cmd2(t_list_cmd **cmd, t_list_cmd *tmp, t_list_cmd *nxt_sta, int i)
{
	while (i--)
		tmp = tmp->next;
	c_lst_remove_next_one(tmp);
	tmp->next = NULL;
	*cmd = nxt_sta;
}

int		split_cmd(t_list_line **lst_line, t_list_cmd *cmd, int i)
{
	t_list_cmd	*next_start;
	t_list_cmd	*tmp;

	while (cmd)
	{
		if (cmd->flags & (F_PIPE + F_SEMICOLON) || (cmd->flags & F_REDIRS &&
				(!cmd->next || cmd->next->flags & F_REDIRS)))
			return (FAILURE);
		if (cmd->next && (cmd->next->flags & (F_PIPE + F_SEMICOLON)))
		{
			if (!(next_start = cmd->next->next))
				return (FAILURE);
			if (cmd->next->flags & F_PIPE)
				(*lst_line)->pipe = 1;
			l_lst_add_back(lst_line, l_lst_new(next_start));
			tmp = (*lst_line)->cmd;
			split_cmd2(&cmd, tmp, next_start, i);
			return (split_cmd(&((*lst_line)->next), cmd, 0));
		}
		i++;
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int		parse_input(char *input, t_list_line **lst_line, t_list *env)
{
	t_list_cmd	*cmd;

	cmd = NULL;
	if (input_to_command(input, &cmd))
		return (FAILURE);
	flag_dollar_and_replace_tild(cmd, env);
	delete_empty_elements(&cmd);
	if (cmd)
	{
		l_lst_add_back(lst_line, l_lst_new(cmd));
		if (split_cmd(lst_line, cmd, 0))
			return (FAILURE);
	}
	return (SUCCESS);
}
