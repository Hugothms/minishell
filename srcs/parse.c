/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/20 09:14:25 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_all_var_env(t_list_cmd *cmd, char **envp, int i)
{
	int		azerty;
	int		size;

	azerty = 0;
	while (envp[azerty])
	{
		if (!ft_strncmp(envp[azerty], &(cmd->str[i + 1]), ft_strlen(&(cmd->str[i])) - 1) && envp[azerty][ft_strlen(&(cmd->str[i])) - 1] == '=')
		{
			size = ft_strlen(&(cmd->str[i]));
			cmd->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/¯
			cmd->str = ft_strjoin_free(cmd->str, &(envp[azerty][size]));
			return ;
		}
		azerty++;
	}
	cmd->str[i] = '\0';
}

void	err_code(t_list_cmd *cmd, char **envp)
{
	ft_putstr_fd("err_code\n", STDERR);
	//!to do
	return ;
}

int 	delete_backslashes(t_list_cmd *cmd, char **envp)
{
	int		i;

	while (cmd)
	{
		i = 0;
		while (cmd->str && !(cmd->flags & F_SIMPLE_QUOTES) && cmd->str[i])
		{
			if (cmd->str[i] == '\\')
			{
				if (cmd->str[i + 1])
					ft_strcpy(&cmd->str[i], &cmd->str[i + 1]);
				else
					return (FAILURE);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int		replace_dollar_and_tild(t_list_cmd *cmd, char **envp)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			if (cmd->str[i] == '$' && !escaped(cmd->str, i) && !(cmd->flags & F_SIMPLE_QUOTES) && cmd->str[i + 1] > 32)
			{
				if (cmd->str[i + 1] == '?')
					err_code(cmd, envp);
				else
					replace_all_var_env(cmd, envp, i);
			}
			else if (cmd->str[i] == '~' && !escaped(cmd->str, i) && !in_quotes(cmd) && (!cmd->str[i + 1] || cmd->str[i + 1] == '/'))
			{
				tmp = cmd->str;
				cmd->str = ft_strdup(&find_var_env(envp, "HOME=")[5]);
				free(tmp);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	delete_empty_elements(t_list_cmd *cmd)
{
	t_list_cmd	*tmp;

	while (cmd)
	{
		if (cmd->next)
		{
			if (!ft_strlen(cmd->next->str) && !in_quotes(cmd->next))
				c_lst_remove_next_one(cmd);
		}
		cmd = cmd->next;
	}
}

int		split_cmd(t_list_line **lst_line, t_list_cmd *cmd, int i)
{
	t_list_cmd	*next_start;
	t_list_cmd	*current_start;

	if (cmd && (cmd->flags & F_SEPARATOR))
		return (FAILURE);
	while (cmd)
	{
		if (cmd->next && (cmd->next->flags & F_SEPARATOR))
		{
			(*lst_line)->separator = get_separator(cmd->next->str);
			if (!(next_start = cmd->next->next))
				return (FAILURE);
			l_lst_add_back(lst_line, l_lst_new(next_start, '\0'));
			t_list_cmd *tmp = (*lst_line)->cmd;
			while (i--)
				tmp = tmp->next;
			c_lst_free_one(tmp->next);
			tmp->next = NULL;
			cmd = next_start;
			return (split_cmd(&((*lst_line)->next), cmd, 0));
		}
		i++;
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int		parse_input(char *input, t_list_line **lst_line, char **envp)
{
	t_list_cmd	*cmd;

	cmd = NULL;
	if (input_to_command(input, &cmd))
		return (FAILURE);
	replace_dollar_and_tild(cmd, envp);
	if (delete_backslashes(cmd, envp))
		return (FAILURE);
	delete_empty_elements(cmd);
	l_lst_add_back(lst_line, l_lst_new(cmd, '\0'));
	if (split_cmd(lst_line, cmd, 0))
		return (FAILURE);
	return (SUCCESS);
}
