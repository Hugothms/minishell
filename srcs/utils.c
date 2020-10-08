/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/08 14:53:53 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\');
}

int		in_quotes(t_list_cmd *cmd)
{
	return ((cmd->flags & SIMPLE_QUOTES) || \
	(cmd->flags & DOUBLE_QUOTES));
}

void	parse_error_exit(char *input)
{
	ft_putstr("minishell: parse error\n");
	free(input);
	exit(1);
}
