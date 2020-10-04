/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 13:10:59 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	replace_dollar(t_list_command **command, char **envp)
{
	int i;

	i = 0;
	while (command)
	{
		// if (command == '$' && ft_isascii(input[i + 1]))
		// {
		// 	if (input[ i + 1] == '?')
		// 		print err code();
		// 	replace_var_env();
		// }
		*command = (*command)->next;
	}
	return (0);
}

void	ancien_parsing_a_supprimer(char *input, t_list_command **command)
{
	char **tmp;
	int i;
	tmp = ft_split_set(input, WHITESPACES);
	i = 0;
	if(tmp[i])
		*command = c_lstnew(tmp[i++], '?'); // create fisrt element of the list
	while(tmp[i])
		c_lstadd_back(command, c_lstnew(tmp[i++], '?')); // fill the list
	ft_free_tab(tmp);
}

int		parse_input(char *input, t_list_command **command, char **envp)
{
	t_parse		par;

	init_par(&par);
	while (input[par.i])
	{
		if(input[par.i] == '\'' && !par.in_double)
			simple_quotes(input, command, &par);
		else if(input[par.i] == '\"' && !par.in_simple)
			double_quotes(input, command, &par);
		// si je suis sur un mot et hors de quotes
		else if (!ft_in_charset(input[par.i], WHITESPACES) && !par.in_simple && !par.in_double)
			end_word(input, command, &par);
		par.i++;
	}
	// replace_dollar(command, envp);
	// ancien_parsing_a_supprimer(input, command);
	return (par.in_simple || par.in_double);
}
