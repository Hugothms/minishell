/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/26 15:01:26 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_all_var_env(t_list_cmd *cmd, char **envp, int i)
{
	int		azerty;
	int		size;
	int		pos_equal;
	char	*after_equal;

	azerty = 0;
	while (envp[azerty])
	{
		pos_equal = 0;
		while (cmd->str[pos_equal] && cmd->str[pos_equal] != '=')
			pos_equal++;
		size = ft_strlen(&(cmd->str[i]));
		if (pos_equal && pos_equal < size)
			size = pos_equal;
		if (!ft_strncmp(envp[azerty], &(cmd->str[i + 1]), size - 1) && envp[azerty][size - 1] == '=')
		{
			after_equal = ft_strdup(&cmd->str[pos_equal]);
			ft_printf("((((((((((((%s)))))))))%d)))%s\n", &cmd->str[i], pos_equal, after_equal);
			cmd->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/¯
			cmd->str = ft_strjoin_free(cmd->str, &(envp[azerty][size]));
			if (pos_equal)
				cmd->str = ft_strjoin_free(cmd->str, after_equal);
			free(after_equal);
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
		while (cmd->str && !(cmd->flags & F_SIMPLE_QUOTE) /*&& !(cmd->flags & F_SIMPLE_QUOTE)*/ && cmd->str[i])
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
			if (cmd->str[i] == '$' && !escaped(cmd->str, i) && !(cmd->flags & F_SIMPLE_QUOTE) && cmd->str[i + 1] > 32)
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
	t_list_cmd	*tmp;

	while (cmd)
	{
		// ft_printf("ici%d\n", cmd->flags);
		// ft_printf("aze%d\n", (*lst_line)->cmd->flags);
		// ft_printf("f:%d\t%s\n", cmd->next->flags, cmd->next->str);
		if (cmd->flags & (F_PIPE + F_SEMICOLON) || (cmd->flags & F_REDIRS && (!cmd->next || cmd->next->flags & F_REDIRS)))
			return (FAILURE);
		if (cmd->next && (cmd->next->flags & (F_PIPE + F_SEMICOLON)))
		{
			//(*lst_line)->cmd->flags = get_flags(cmd->next->str);
			// ft_printf("\nsplit:%s\n", cmd->next->str);
			// ft_printf("flags:%d\n", (*lst_line)->cmd->flags);
			if (cmd->next->flags & F_SEMICOLON || cmd->next->flags & F_PIPE)
			{
				if (!(next_start = cmd->next->next))
					return (FAILURE);
				if (cmd->next->flags & F_PIPE)
					(*lst_line)->pipe = 1;
				l_lst_add_back(lst_line, l_lst_new(next_start));
				tmp = (*lst_line)->cmd;
				while (i--)
					tmp = tmp->next;
				// ft_printf("tmp:%s\n", tmp->str);
				c_lst_remove_next_one(tmp);
				tmp->next = NULL;
				cmd = next_start;
				// ft_printf("flags:%d\n", (*lst_line)->cmd->flags);
				return (split_cmd(&((*lst_line)->next), cmd, 0));
			}
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

	// ft_printf("CMD:\n-----------------\n");
	// t_list_cmd	*copy = cmd;
	// while (copy)
	// {
	// 	ft_printf("F:%d\t%s\n", copy->flags, copy->str);
	// 	copy = copy->next;
	// }
	// ft_printf("-----------------\n\n");

	if (delete_backslashes(cmd, envp))
		return (FAILURE);
	delete_empty_elements(cmd);
	l_lst_add_back(lst_line, l_lst_new(cmd));
	if (split_cmd(lst_line, cmd, 0))
		return (FAILURE);
	return (SUCCESS);
}
