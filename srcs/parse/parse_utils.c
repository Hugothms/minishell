/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:52:06 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/07 14:17:15 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_empty_elements(t_list_cmd **cmd)
{
	t_list_cmd	*tmp;
	t_list_cmd	*next_one;

	tmp = *cmd;
	while (tmp && !ft_strlen(tmp->str) && !in_quotes(tmp))
	{
		next_one = tmp->next;
		c_lst_free_one(tmp);
		*cmd = next_one;
		tmp = next_one;
	}
	while (tmp && tmp->next)
	{
		if (!ft_strlen(tmp->next->str) && !in_quotes(tmp->next))
		{
			c_lst_remove_next_one(tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}

void	word(char *input, t_list_cmd **cmd, t_parse *par)
{
	while (input[par->pos] && ((ft_in_charset(input[par->pos], WSP))))
		par->pos++;
	if (input[par->i + 1] && !ft_in_charset(input[par->i + 1], WSP))
		add_cmd(&input[par->pos], cmd, par->i - par->pos + 1, F_NO_SP_AFTER);
	else
		add_cmd(&input[par->pos], cmd, par->i - par->pos + 1, F_NOTHING);
	par->pos = par->i + 1;
}

int		is_in_word(char *input, t_parse *par)
{
	return (((!ft_in_charset(input[par->i], WSP) ||\
	escaped(input, par->i)) ||\
	(!ft_in_charset(input[par->i], "\'\"") || escaped(input, par->i)))\
	&& !par->in_simple && !par->in_double);
}

int		check_del_backslash(t_list_cmd *cmd, int i)
{
	if ((cmd->flags & F_SIMPLE_QUOTE || (cmd->flags & F_DOUBLE_QUOTE)) &&
			(!ft_in_charset(cmd->str[i + 1], "\\\"`$")))
		return (1);
	else
		return (0);
}
