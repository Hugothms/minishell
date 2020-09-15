/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/16 00:54:29 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd()
{
	char	*pwd = getcwd(NULL, 0);
	ft_putstr("\xF0\x9F\x98\x8D \xF0\x9F\x99\x88 \xF0\x9F\x92\x96 \xF0\x9F\x8C\x9F \xE2\x9C\x85 ");
	ft_putstr(pwd);
	ft_putchar(' ');
	free(pwd);
}

int		main(const int argc, const char *argv[])
{
	char	*line;

	ft_putstr(WELCOME_MSG);
	pwd();
	get_next_line_custom(&line);
	ft_putstr(line);
	free(line);
	return (0);
}
