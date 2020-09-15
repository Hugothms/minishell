/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/15 21:16:23 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd()
{
	char	*pwd = getcwd(NULL, 0);
	ft_putstr(pwd);
}

int		main(const int argc, const char *argv[])
{
	char	*line;

	pwd();
	get_next_line(0, &line);
	ft_putstr(line);
	return (0);
}
