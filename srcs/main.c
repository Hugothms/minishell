/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/23 10:43:31 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(&envp[i][5], ':');
	return (path);
}

int		search_command(char *command, char **path)
{
	int i;

	i = 0;
	while (path[i])
	{
		DIR *dir = opendir(path[i]);
		struct dirent *dirent = readdir(dir);
		ft_putchar(dirent->d_name);
		ft_putchar('\n');
		ft_putchar(dirent->d_type);
		ft_putchar('\n');
		ft_putnbr(dirent->d_reclen);
		ft_putchar('\n');
		ft_putnbr(dirent->d_ino);
		ft_putchar('\n');
		ft_putnbr(dirent->d_off);
		ft_putchar('\n');
		closedir(dir);
		ft_putchar('\n');
		i++;
	}
	return (0);
}

char	*exec_command(char **command, char **path)
{
	char *ret;
	char *tmp;

	if(!command)
		return (NULL);
	// else if (!(command[0]))
	// 	return (NULL);
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
	else if(search_command(*command, path))
	{
		ret = ft_strjoin("minishell: command not found: ", command[0]);
		tmp = ret;
		ret = ft_strjoin(ret, "\n");
		free(tmp);
		return (ret);
	}
}

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr("\xE2\x9E\xA1 ");
	pwd = getcwd(NULL, 0);
	ft_putstr(pwd);
	free(pwd);
	ft_putstr(": ");
}

int		main(const int argc, const char *argv[], char *envp[])
{
	char	*input;
	char	**command;
	char	*ret;
	char	**path;

	// ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while(1)
	{
		free(input);
		print_prompt();
		get_next_line_custom(&input);
		if(parse_input(input, &command))
		{
			ft_putstr("minishell: parse error\n");
			free(input);
			exit(1);
		}
		if(*command)
		{
			path = get_path(envp);
			if(ret = exec_command(command, path))
			{
				ft_putstr(ret);
				free(ret);
			}
			ft_free_tab(path);
			free(path);
			ft_free_tab(command);	
		}
		free(command);
	}
	free(input);
	return (0);
}
