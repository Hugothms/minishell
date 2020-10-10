/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/10 18:24:21 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\');
}

int	is_separator(char *str)
{
	return (ft_in_charset(*str, SEPARATORS) || ft_strncmp(str, ">>", 2));
}

int		in_quotes(t_list_cmd *cmd)
{
	return ((cmd->flags & F_SIMPLE_QUOTES) || \
	(cmd->flags & F_DOUBLE_QUOTES));
}

void	parse_error_exit(char *input)
{
	ft_putstr("minishell: parse error\n");
	free(input);
	exit(1);
}
