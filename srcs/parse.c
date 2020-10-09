/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/08 14:54:01 by hthomas          ###   ########.fr       */
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
			cmd->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/
			cmd->str = ft_strjoin_free(cmd->str, &(envp[azerty][size]));
			return ;
		}
		azerty++;
	}
	cmd->str[i] = '\0';
}

void	err_code(t_list_cmd *cmd, char **envp)
{
	ft_putstr("err_code\n");
	//!to do
	return ;
}

// int 	deal_backslash(t_list_command *cmd, char **envp)
// {
// 	int		i;

// 	while (cmd)
// 	{
// 		i = 0;
// 		while (cmd->str && cmd->str[i])
// 		{
// 			if (cmd->str[i] == '\\' && ...)
// 			{
// 				//? i++;
// 				//! to do
// 			}
// 			i++;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }

int		replace_dollar_and_tild(t_list_cmd *cmd, char **envp)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			if (cmd->str[i] == '$' && !(cmd->flags & SIMPLE_QUOTES) && cmd->str[i + 1] > 32)
			{
				if (cmd->str[i + 1] == '?')
					err_code(cmd, envp);
				else
					replace_all_var_env(cmd, envp, i);
			}
			else if (cmd->str[i] == '~' && !in_quotes(cmd) && (!cmd->str[i + 1] || cmd->str[i + 1] == '/'))
			{
				tmp = cmd->str;
				cmd->str = ft_strdup(&find_var_env(envp, "HOME=")[5]);
				free(tmp);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	delete_empty_elements(t_list_cmd *cmd)
{
	t_list_cmd	*tmp;

	while (cmd)
	{
		if (cmd->next)
		{
			if (!ft_strlen(cmd->next->str) && !in_quotes(cmd->next))
				c_lst_remove_next_one(cmd, c_lst_free_one);
		}
		cmd = cmd->next;
	}
}

// void	ancien_parsing_a_supprimer(char *input, t_list_command **cmd)
// {
// 	char **tmp;
// 	int i;
// 	tmp = ft_split_set(input, WHITESPACES);
// 	i = 0;
// 	if (tmp[i])
// 		*cmd = c_lst_new(tmp[i++], '?'); // create fisrt element of the list
// 	while (tmp[i])
// 		c_lst_add_back(cmd, c_lst_new(tmp[i++], '?')); // fill the list
// 	ft_free_tab(tmp);
// }

int		input_quotes_to_command(char *input, t_list_cmd **cmd)
{
	t_parse		par;

	init_par(&par);
	while (input[par.i])
	{
		if (input[par.i] == '\'' && !par.in_double && !escaped(input, par.i))
			simple_quotes(input, cmd, &par);
		else if (input[par.i] == '\"' && !par.in_simple && !escaped(input, par.i))
			double_quotes(input, cmd, &par);
		// si je suis sur un mot et hors de quotes
		else if (!ft_in_charset(input[par.i], WHITESPACES) && !par.in_simple && !par.in_double)
			end_word(input, cmd, &par);
		par.i++;
	}
	return (par.in_simple || par.in_double);
}

int		parse_input(char *input, t_list_cmd **cmd, char **envp)
{
	if (input_quotes_to_command(input, cmd))
		return (ERR);
	// deal_backslash(*cmd, envp);
	replace_dollar_and_tild(*cmd, envp);
	// ancien_parsing_a_supprimer(input, cmd);
	delete_empty_elements(*cmd);
}
