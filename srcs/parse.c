/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/02 18:40:55 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int		count_quotes(char *input)
// {
// 	int		cpt;
// 	int		i;
// 	int		in_simple;
// 	int		in_double;

// 	in_simple = 0;
// 	in_double = 0;
// 	cpt = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if(input[i] == '\'' && !in_double)
// 		{
// 			in_simple += (in_simple == 0 ? 1 : -1);
// 			if (!in_simple)
// 				cpt += 2;
// 		}
// 		if(input[i] == '\"' && !in_simple)
// 		{
// 			in_double += (in_double == 0 ? 1 : -1);
// 			if (!in_double)
// 				cpt += 2;
// 		}
// 		i++;
// 	}
// 	if (in_simple || in_double)
// 		return (-1);
// 	return (cpt + 1);
// }

// int		function(char *input, t_list_command *command, int c)
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
// 				if (function(&input[i + 1], command, c))
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

// int		open_quotes(char *input, t_list_command *command)
// {
// 	int nb_quotes;

// 	if ((nb_quotes = count_quotes(input)) == -1)
// 		return (1);
// 	*command = malloc(sizeof(**command) * (nb_quotes + 1));
// 	int ret = function(input, command, 0);
	
// 	return (ret);
// }

// int 	dollar(char *input, t_list_command *command)
// {
// 	int i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '$' && ft_isascii(input[i + 1]))
// 		{
// 			// replace_var_env();
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int		count_words(const char *str, char *charset)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i])
// 		{
// 			if (!ft_in_charset(str[i], charset))
// 			{
// 				count++;
// 				break ;
// 			}
// 			i++;
// 		}
// 		while (str[i])
// 		{
// 			if (ft_in_charset(str[i++], charset))
// 				break ;
// 		}
// 	}
// 	return (count);
// }


int		parse_input(char *input, t_list_command **command)
{
	char **tmp;
	int i;
	
	tmp = ft_split_set(input, " \t");
	i = 0;
	if(tmp[i])
		*command = c_lstnew(tmp[i++], '?'); // create fisrt element of the list
	while(tmp[i])
		c_lstadd_back(command, c_lstnew(tmp[i++], '?')); // fill the list
	ft_free_tab(tmp);
	free(tmp);
	return (0);
}
