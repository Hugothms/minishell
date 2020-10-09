/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 11:22:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\');
}

int		in_quotes(t_list *cmd)
{
	return ((((t_word*)cmd->content)->flags & SIMPLE_QUOTES) || \
	(((t_word*)cmd->content)->flags & DOUBLE_QUOTES));
}

void	parse_error_exit(char *input)
{
	ft_putstr("minishell: parse error\n");
	free(input);
	exit(1);
}
