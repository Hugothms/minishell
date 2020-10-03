/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 00:44:48 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int		quotes(char *input, t_list_command *command, int c)
// {
// 	int	in_simple;
// 	int	in_double;
// 	int	pos;
// 	int	i;

// 	in_simple = 0;
// 	in_double = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if(input[i] == '\"' && !in_double)
// 		{
// 			if (!in_simple)
// 				pos = i;
// 			else
// 			{
// 				if (pos != 0)
// 					(*command)[c++] = ft_strndup(input, pos);
// 				(*command)[c++] = ft_strndup(&input[pos + 1], i - pos - 1);
// 				(*command)[c] = NULL;
// 				if (quotes(&input[i + 1], command, c))
// 					return (c);
// 				return 0;
// 			}
// 			in_simple += (in_simple == 0 ? 1 : -1);
// 		}

// 		//same same... but different
// 		// else if(input[i] == '\"' && !in_simple)
// 		// {

// 		// 	in_double += (in_double == 0 ? 1 : -1);
// 		// }
// 		i++;
// 	}
// 	return (in_simple || in_double);
// }

int 	dollar(char *input, t_list_command *command)
{
	int i;

	i = 0;
	while (input[i])
	{
		// if (input[i] == '$' && ft_isascii(input[i + 1]))
		// {
		// 	if (input[ i + 1] == '?')
		// 		print err code();
		// 	replace_var_env();
		// }
		i++;
	}
	return (0);
}

void	default_tmp(char *input, t_list_command **command)
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

char	**lst_to_strs(t_list_command *command);

int		parse_input(char *input, t_list_command **command)
{
	int	in_simple;
	int	in_double;
	int	pos;
	int	i;

	in_simple = 0;
	in_double = 0;
	i = 0;
	pos = 0;
	while (input[i])
	{
		if(input[i] == '\'' && !in_double)
		{
			if (in_simple)
			{
				char *str = ft_strndup(&input[pos + 1], i - pos - 1);
				c_lstadd_back(command, c_lstnew(str, SIMPLE_QUOTES));
			}
			pos = i;
			in_simple += (in_simple == 0 ? 1 : -1);
		}
		//same same... but different
		// else if(input[i] == '\"' && !in_simple)
		// {
		// 	in_double += (in_double == 0 ? 1 : -1);
		// }

		// si je suis sur un mot et hors de quotes
		else if (!ft_in_charset(input[i], WHITESPACES) && !in_simple && !in_double)
		{
			// si je suis sur le dernier caractere du mot
			if(!input[i + 1] || ft_in_charset(input[i + 1], WHITESPACES))
			{
				while(ft_in_charset(input[pos], WHITESPACES))
					pos++;
				char *str = ft_strndup(&input[pos], i - pos + 1);
				c_lstadd_back(command, c_lstnew(str, NOTHING));
				free(str);
				pos = i + 1;
			}
		}
		i++;
	}
	// default_tmp(input, command);
	return (0);
}
