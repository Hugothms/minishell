/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/16 16:18:43 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd()
{
	return(getcwd(NULL, 0));
}

void	command(char **input)
{
	char	*tmp;

	ft_putstr(tmp = pwd());
	free(tmp);
	get_next_line_custom(input);
}

int		main(const int argc, const char *argv[])
{
	char	*input;

	// ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while(ft_strcmp(input, "exit"))
	{
		free(input);
		command(&input);
	}
	free(input);
	return (0);
}
