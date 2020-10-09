/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 11:28:30 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_all_var_env(t_list *cmd, char **envp, int i)
{
	int		azerty;
	int		size;

	azerty = 0;
	while (envp[azerty])
	{
		if (!ft_strncmp(envp[azerty], &(((t_word*)cmd->content)->str[i + 1]), ft_strlen(&(((t_word*)cmd->content)->str[i])) - 1) && envp[azerty][ft_strlen(&(((t_word*)cmd->content)->str[i])) - 1] == '=')
		{
			size = ft_strlen(&(((t_word*)cmd->content)->str[i]));
			((t_word*)cmd->content)->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/
			((t_word*)cmd->content)->str = ft_strjoin_free(((t_word*)cmd->content)->str, &(envp[azerty][size]));
			return ;
		}
		azerty++;
	}
	((t_word*)cmd->content)->str[i] = '\0';
}

void	err_code(t_list *cmd, char **envp)
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
// 		while (((t_cmd*)cmd->content)->str && ((t_cmd*)cmd->content)->str[i])
// 		{
// 			if (((t_cmd*)cmd->content)->str[i] == '\\' && ...)
// 			{
// 				//? i++;
// 				//! to do
// 			}
// 			i++;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (OK);
// }

int		replace_dollar_and_tild(t_list *cmd, char **envp)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (((t_word*)cmd->content)->str && ((t_word*)cmd->content)->str[i])
		{
			if (((t_word*)cmd->content)->str[i] == '$' && !(((t_word*)cmd->content)->flags & SIMPLE_QUOTES) && ((t_word*)cmd->content)->str[i + 1] > 32)
			{
				if (((t_word*)cmd->content)->str[i + 1] == '?')
					err_code(cmd, envp);
				else
					replace_all_var_env(cmd, envp, i);
			}
			else if (((t_word*)cmd->content)->str[i] == '~' && !in_quotes(cmd) && (!((t_word*)cmd->content)->str[i + 1] || ((t_word*)cmd->content)->str[i + 1] == '/'))
			{
				tmp = ((t_word*)cmd->content)->str;
				((t_word*)cmd->content)->str = ft_strdup(&find_var_env(envp, "HOME=")[5]);
				free(tmp);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (OK);
}

void	delete_empty_elements(t_list *cmd)
{
	t_list	*tmp;

	while (cmd)
	{
		if (cmd->next)
		{
			if (!ft_strlen(((t_word*)cmd->next->content)->str) && !in_quotes(cmd->next))
				ft_lstremove_next_one(cmd, free_cmd);
		}
		cmd = cmd->next;
	}
}

int		input_quotes_to_command(char *input, t_list **p_cmd)
{
	t_parse		par;

	par.in_simple = 0;
	par.in_double = 0;
	par.i = 0;
	par.pos = 0;
	while (input[par.i])
	{
		if (input[par.i] == '\'' && !par.in_double && !escaped(input, par.i))
			simple_quotes(input, p_cmd, &par);
		else if (input[par.i] == '\"' && !par.in_simple && !escaped(input, par.i))
			double_quotes(input, p_cmd, &par);
		// si je suis sur un mot et hors de quotes
		else if (!ft_in_charset(input[par.i], WHITESPACES) && !par.in_simple && !par.in_double)
			end_word(input, p_cmd, &par);
		par.i++;
	}
	return (par.in_simple || par.in_double);
}

t_word	*new_word(char *str)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	word->str = ft_strdup(str);
	return (word);
}

void	ancien_parsing_a_supprimer(char *input, t_list *cmd)
{
	char	**tmp;
	int		i;
	t_word	*word;
	
	tmp = ft_split_set(input, WHITESPACES);
	i = 0;
	if (tmp[i])
	{
		word = new_word(tmp[i++]);
		cmd = ft_lstnew(word); // create fisrt element of the list
	}
	while (tmp[i])
	{
		word = new_word(tmp[i++]);
		ft_lstadd_back(&cmd, ft_lstnew(word)); // fill the list
	}
	ft_putstr(((t_word*)cmd->content)->str);
	ft_free_tab(tmp);
}

int		parse_input(char *input, t_list *lst_cmd, char **envp)
{
	t_word		*empty;
	t_list_cmd	new;

	ft_lstadd_back(&lst_cmd, ft_lstnew(empty));
	lst_cmd->content = &new;
	ft_printf("%p: %d\n", lst_cmd, *lst_cmd);
	// if (input_quotes_to_command(input, &((t_list_cmd*)lst_cmd->content)->cmd))
	// 	return (ERR);
	// deal_backslash(*((t_list_cmd*)lst_cmd->content)->cmd, envp);
	// replace_dollar_and_tild(((t_list_cmd*)lst_cmd->content)->cmd, envp);
	ancien_parsing_a_supprimer(input, ((t_list_cmd*)lst_cmd->content)->cmd);
	ft_printf("%p\n", (((t_word*)((t_list_cmd*)lst_cmd->content)->cmd->content)));
	ft_putchar('\n');
	ft_putnbr((((t_word*)((t_list_cmd*)lst_cmd->content)->cmd->content))->str);
	ft_putchar('\n');
	// delete_empty_elements(((t_list_cmd*)lst_cmd->content)->cmd);
	// lst_cmd->next = NULL;
	return (OK);
}
