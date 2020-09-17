/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/17 15:06:25 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*pwd()
{
	return(getcwd(NULL, 0));
}

char	*echo(char **args)
{
	int		i;
	char	*ret;

	// if (echo_args_valid())
	{
		i = 0;
		while(args[i])
		{
			ft_strjoin(ret, args[i]);
			ft_strjoin(args[i], " ");
		}
	}
	return (ret);
}

int		parse_input(char *line, char **args)
{

	return (1);
}

int		command_valid(char *input)
{
	char	*tmp;
	char	**command;

	ft_putstr(tmp = pwd());
	free(tmp);
	get_next_line_custom(&input);
	if(!parse_input(input, command))
	{
		ft_putstr("minishell: parse error");
		exit(1);
	}
	exec_command(command);
	return (1);
}

int		main(const int argc, const char *argv[])
{
	char	*input;

	// ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while(1)
	{
		free(input);
		if (!command_valid(input))
			break;
	}
	free(input);
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	ft_putstr(ft_strjoin_sep(10, argv, "q"));
// 	return 0;
// }
