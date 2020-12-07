/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 15:17:06 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_par(t_parse *par)
{
	par->in_simple = 0;
	par->in_double = 0;
	par->i = 0;
	par->pos = 0;
}

void	add_cmd(char *input, t_list_cmd **cmd, int size, int flags)
{
	char *str;

	if (size < 0)
		return ;
	else if (size == 0)
		str = ft_strdup("");
	else
	{
		while (!(flags & F_SIMPLE_QUOTE) && !(flags & F_DOUBLE_QUOTE)\
		&& ft_in_charset(*input, WSP))
			input++;
		str = ft_strndup(input, size);
	}
	c_lst_add_back(cmd, c_lst_new(str, flags));
	free(str);
}

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\' && !escaped(str, i - 1));
}

int		is_separator(char *str, int i)
{
	return (ft_in_charset(str[i], SYMBOLS) || !ft_strncmp(&str[i], ">>", 2));
}

int		in_quotes(t_list_cmd *cmd)
{
	return ((cmd->flags & F_SIMPLE_QUOTE) || \
	(cmd->flags & F_DOUBLE_QUOTE));
}
