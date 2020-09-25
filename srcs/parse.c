/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:09 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/25 16:00:29 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_quotes(char	*input)
{
	int		cpt;
	int		i;
	int		in_simple;
	int		in_double;

	in_simple = 0;
	in_double = 0;
	cpt = 0;
	i = 0;
	while (input[i])
	{
		if(input[i] == '\'' && !in_double)
		{
			in_simple += (in_simple == 0 ? 1 : -1);
			if (!in_simple)
				cpt += 2;
		}
		if(input[i] == '\"' && !in_simple)
		{
			in_double += (in_double == 0 ? 1 : -1);
			if (!in_double)
				cpt += 2;
		}
		i++;
	}
	if (in_simple || in_double)
		return (-1);
	ft_putnbr(cpt);
	ft_putchar('\n');
	return (cpt);
}

int		function(char *input, char ***command)
{
	int	in_simple;
	int	in_double;
	int	pos;
	int	i;
	int	c;

	in_simple = 0;
	in_double = 0;
	c = 0;
	i = 0;
	while (input[i])
	{
		if(input[i] == '\"' && !in_double)
		{
			if (!in_simple)
				pos = i;
			else
			{
				ft_putstr("ca rempli\n");
				ft_putnbr(pos);
				ft_putstr("\nnb\n");
				(*command)[c++] = ft_strndup(input, pos);
				(*command)[c++] = ft_strndup(&input[pos + 1], i - pos + 1);
				(*command)[c] = NULL;
				ft_putstr("---------*command:\n");
				ft_print_tabstr(*command);
				ft_putstr("---------input:\n");
				ft_putstr(&input[i + 1]);
				ft_putstr("\n---------c:\n");
				ft_putnbr(c);
				ft_putstr("\n---------openquotes:\n");
				if (function(&input[i + 1], &command[c]))
					return (1);
			}			
			in_simple += (in_simple == 0 ? 1 : -1);
		}



		//same same... but different
		// else if(input[i] == '\"' && !in_simple)
		// {

		// 	in_double += (in_double == 0 ? 1 : -1);
		// }
		i++;
	}
	return (in_simple || in_double);
}

int		open_quotes(char *input, char ***command)
{
	int nb_quotes;

	if ((nb_quotes = count_quotes(input)) == -1)
		return (1);
	*command = malloc(sizeof(**command) * (nb_quotes + 1));
	int ret = function(input, command);
	ft_putstr("fin open_quotes\n");
	return (ret);
}

int		parse_input(char *input, char ***command)
{
	if (open_quotes(input, command))
		return (1);
	// *command = ft_split_set(input, " \t");
	return (0);
}
