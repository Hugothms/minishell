/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 01:10:40 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 11:22:39 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	init_par(t_parse *par)
// {
// 	par->in_simple = 0;
// 	par->in_double = 0;
// 	par->i = 0;
// 	par->pos = 0;
// }

void	add_substr_to_cmd(char *input, t_list **p_cmd, int size, int flags)
{
	t_word	*new;

	while (!(flags & SIMPLE_QUOTES) && !(flags & DOUBLE_QUOTES) && ft_in_charset(*input, WHITESPACES))
		input++;
	new->str = ft_strndup(input, size);
	ft_lstadd_back(p_cmd, ft_lstnew(new));
}

void	simple_quotes(char *input, t_list **p_cmd, t_parse *par)
{
	if (!par->in_simple && par->i && !ft_in_charset(input[par->i - 1], WHITESPACES))
		// start quotes just after a word
		add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos - 1, NO_SPACE_AFTER);
	else if (par->in_simple)
	{
		if (input[par->i + 1] && !ft_in_charset(input[par->i + 1], WHITESPACES))
			// end quotes without space after
			add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos, SIMPLE_QUOTES + NO_SPACE_AFTER);
		else
			// end quotes with space after
			add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos, SIMPLE_QUOTES);
	}
	par->pos = par->i + 1;
	par->in_simple += (par->in_simple == 0 ? 1 : -1);
}

void	double_quotes(char *input, t_list **p_cmd, t_parse *par)
{
	if (!par->in_double && par->i && !ft_in_charset(input[par->i - 1], WHITESPACES))
		add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos - 1, NO_SPACE_AFTER);
	else if (par->in_double)
	{
		if (input[par->i + 1] && !ft_in_charset(input[par->i + 1], WHITESPACES))
			add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos, DOUBLE_QUOTES + NO_SPACE_AFTER);
		else
			add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos, DOUBLE_QUOTES);
	}
	par->pos = par->i + 1;
	par->in_double += (par->in_double == 0 ? 1 : -1);
}

void	end_word(char *input, t_list **p_cmd, t_parse *par)
{
	// si je suis sur le dernier caractere du mot
	if (!input[par->i + 1] || ft_in_charset(input[par->i + 1], WHITESPACES))
	{
		while (input[par->pos] && ft_in_charset(input[par->pos], WHITESPACES)) // or  input[par->pos] <= 32) because this is causing leaks when only arrows are pressed
			par->pos++;
		add_substr_to_cmd(&input[par->pos], p_cmd, par->i - par->pos + 1, NOTHING);
		par->pos = par->i + 1;
	}
}
