/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 01:10:40 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 02:00:28 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_substr_to_cmd(char *input, t_list_command **command, int start, int size, int flags)
{
	char *str = ft_strndup(&input[start], size);
	c_lstadd_back(command, c_lstnew(str, flags));
	free(str);
}

void	simple_quotes(char *input, t_list_command **command, t_parse *par)
{
	if(!par->in_simple && par->i && !ft_in_charset(input[par->i - 1], WHITESPACES))		
		add_substr_to_cmd(input, command, par->pos + 1, par->i - par->pos - 1, NO_SPACE_AFTER);
	else if(par->in_simple)
	{
		if (input[par->i + 1] && !ft_in_charset(input[par->i + 1], WHITESPACES))
			add_substr_to_cmd(input, command, par->pos, par->i - par->pos, SIMPLE_QUOTES + NO_SPACE_AFTER);
		else
			add_substr_to_cmd(input, command, par->pos, par->i - par->pos, SIMPLE_QUOTES);
	}
	par->pos = par->i + 1;
	par->in_simple += (par->in_simple == 0 ? 1 : -1);
}

void	double_quotes(char *input, t_list_command **command, t_parse *par)
{
	if(!par->in_double && par->i && !ft_in_charset(input[par->i - 1], WHITESPACES))		
		add_substr_to_cmd(input, command, par->pos + 1, par->i - par->pos - 1, NO_SPACE_AFTER);
	else if(par->in_double)
	{
		if (input[par->i + 1] && !ft_in_charset(input[par->i + 1], WHITESPACES))
			add_substr_to_cmd(input, command, par->pos, par->i - par->pos, DOUBLE_QUOTES + NO_SPACE_AFTER);
		else
			add_substr_to_cmd(input, command, par->pos, par->i - par->pos, DOUBLE_QUOTES);
	}
	par->pos = par->i;
	par->in_double += (par->in_double == 0 ? 1 : -1);
}

void	end_word(char *input, t_list_command **command, t_parse *par)
{
	// si je suis sur le dernier caractere du mot
	if(!input[par->i + 1] || ft_in_charset(input[par->i + 1], WHITESPACES))
	{
		while(ft_in_charset(input[par->pos], WHITESPACES))
			par->pos++;
		add_substr_to_cmd(input, command, par->pos, par->i - par->pos + 1, NOTHING);
		par->pos = par->i + 1;
	}
}

void	init_par(t_parse *par)
{
	par->in_simple = 0;
	par->in_double = 0;
	par->i = 0;
	par->pos = 0;
}