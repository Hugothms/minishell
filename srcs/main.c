/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/18 16:08:09 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exec_command(char **command)
{
	if(!command)
		return (NULL);
	else if (!(command[0]))
		return (NULL);
	else if (!ft_strcmp(command[0], "echo"))
		return(ft_echo(&command[1]));
	else if (!ft_strcmp(command[0], "cd"))
		return(ft_cd(&command[1]));
	else if (!ft_strcmp(command[0], "pwd"))
		return(ft_pwd());
	else if (!ft_strcmp(command[0], "export"))
		return(ft_export(&command[1]));
	else if (!ft_strcmp(command[0], "unset"))
		return(ft_unset(&command[1]));
	else if (!ft_strcmp(command[0], "env"))
		return(ft_env(&command[1]));
	else if (!ft_strcmp(command[0], "exit"))
		return(ft_exit(&command[1]));
	else
		return (ft_strjoin("minishell: command not found: ", command[0]));
}

void	print_pwd_msg()
{
	char	*pwd;

	ft_putstr("\xE2\x9E\xA1 ");
	pwd = ft_pwd();
	ft_putstr(pwd);
	free(pwd);
	ft_putstr(": ");
}

int		main(const int argc, const char *argv[])
{
	char	*input;
	char	**command;
	char	*ret;

	// ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while(1)
	{
		free(input);
		print_pwd_msg();
		get_next_line_custom(&input);
		if(parse_input(input, &command))
		{
			ft_putstr("minishell: parse error\n");
			exit(1);
		}
		if(command)
		{
			if(ret = exec_command(command))
			{
				ft_putstr_clean(ret);
				free(ret);
			}
			ft_free_tab(command);
			free(command);
		}
	}
	free(input);
	return (0);
}
