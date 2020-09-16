/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/16 14:34:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd()
{
	return(getcwd(NULL, 0));
}

int		main(const int argc, const char *argv[])
{
	char	*line;
	char	*tmp;

	// ft_putstr(WELCOME_MSG);
	ft_putstr(tmp = pwd());
	free(tmp);
	get_next_line_custom(&line);
	ft_putstr(line);
	free(line);
	return (0);
}
