/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/06 21:20:28 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_all_var_env(t_list_command *command, char **envp, int i)
{
	int		azerty;
	int		size;

	azerty = 0;
	while (envp[azerty])
	{
		if (!ft_strncmp(envp[azerty], &(command->str[i+1]), ft_strlen(&(command->str[i])) - 1) && envp[azerty][ft_strlen(&(command->str[i])) - 1] == '=')
		{
			size = ft_strlen(&(command->str[i]));
			command->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/
			command->str = ft_strjoin_free(command->str, &(envp[azerty][size]));
			return ;
		}
		azerty++;
	}
	command->str[i] = '\0';
	if (!ft_strlen(&command->str))
		c_lstdelone(&command, c_free);
}

void	err_code(t_list_command *command, char **envp)
{
	ft_putstr("err_code\n");
	return ;
}

// int 	deal_backslash(t_list_command *command, char **envp)
// {
// 	int		i;

// 	while (command)
// 	{
// 		i = 0;
// 		while (command->str && command->str[i])
// 		{
// 			if (command->str[i] == '$' && !(command->flags & SIMPLE_QUOTES) && command->str[i + 1] > 32)
// 			{
// 				continue ;
// 			}
// 			i++;
// 		}
// 		command = command->next;
// 	}
// 	return (0);
// }

int 	replace_dollar_and_tild(t_list_command *command, char **envp)
{
	int		i;
	char	*tmp;

	while (command)
	{
		i = 0;
		while (command->str && command->str[i])
		{
			if (command->str[i] == '$' && !(command->flags & SIMPLE_QUOTES) && command->str[i + 1] > 32)
			{
				if (command->str[i + 1] == '?')
					err_code(command, envp);
				else
					replace_all_var_env(command, envp, i);
			}
			else if (command->str[i] == '~' && !(command->flags & SIMPLE_QUOTES) && !(command->flags & DOUBLE_QUOTES) && (!command->str[i + 1] || command->str[i + 1] == '/'))
			{
				tmp = command->str;
				command->str = ft_strdup(&find_var_env(envp, "HOME=")[5]);
				free(tmp);
			}
			i++;
		}
		command = command->next;
	}
	return (0);
}

// void	delete_empty_elements(command);
// {
// 	while (command)
// 	{
// 		if(!command->next)
// 		{
// 			c_lstdelone(command, c_free);
// 			return ;
// 		}
// 		if (!ft_strlen(command->str))
// 			c_lstdelone(command, c_free);
// 		command = command->next;
// 	}
// }

// void	ancien_parsing_a_supprimer(char *input, t_list_command **command)
// {
// 	char **tmp;
// 	int i;
// 	tmp = ft_split_set(input, WHITESPACES);
// 	i = 0;
// 	if(tmp[i])
// 		*command = c_lstnew(tmp[i++], '?'); // create fisrt element of the list
// 	while(tmp[i])
// 		c_lstadd_back(command, c_lstnew(tmp[i++], '?')); // fill the list
// 	ft_free_tab(tmp);
// }

int		parse_input(char *input, t_list_command **command, char **envp)
{
	t_parse		par;

	init_par(&par);
	while (input[par.i])
	{
		if(input[par.i] == '\'' && !par.in_double && !escaped(input, par.i))
			simple_quotes(input, command, &par);
		else if(input[par.i] == '\"' && !par.in_simple && !escaped(input, par.i))
			double_quotes(input, command, &par);
		// si je suis sur un mot et hors de quotes
		else if (!ft_in_charset(input[par.i], WHITESPACES) && !par.in_simple && !par.in_double)
			end_word(input, command, &par);
		par.i++;
	}
	// deal_backslash(*command, envp);
	replace_dollar_and_tild(*command, envp);
	// ancien_parsing_a_supprimer(input, command);
	// delete_empty_elements(command);
	return (par.in_simple || par.in_double);
}
