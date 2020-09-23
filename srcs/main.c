/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/23 18:01:10 by hthomas          ###   ########.fr       */
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

int		try_path(char **command, char **envp, t_execve exec)
{
	int		i;
	int		cpt;
	int		ret;
	char	**path;
	char	*full_path;
	char	*tmp;

	path = get_path(envp);
	i = 0;
	cpt = 0;
	ret = 1;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], "/");
		tmp = full_path;
		full_path = ft_strjoin(full_path, *command);
		free(tmp);
		if(execve(full_path, command, exec.envp))
			cpt++;
		free(full_path);
		if(i != cpt)
			ret = 0;
		i++;
	}
	ft_free_tab(path);
	free(path);
	return (ret);
}

int		search_command(char **command, char **envp, t_execve exec)
{
	int	ret;

	ret = 1;
	pid_t pid = fork();
	if (pid == 0)
	{
		if(try_path(command, envp, exec))
			exit(0);
	}
	else
	{
		ret = 0;
		wait(0);
	}
	return (ret);
}

void	not_found(char *command)
{
	char *ret;
	char *tmp;

	ret = ft_strjoin("minishell: command not found: ", command);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	free(tmp);
	ft_putstr(ret);
	free(ret);
	exit(0);
}

char	*exec_command(char **command, char **envp, t_execve exec)
{
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
	else if(search_command(command, envp, exec))
		not_found(command[0]);
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

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	char		**command;
	char		*ret;
	t_execve	exec;

	// ft_putstr(WELCOME_MSG);
	exec.argv = argv;
	exec.envp = envp;
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
			if(ret = exec_command(command, envp, exec))
			{
				ft_putstr(ret);
				free(ret);
			}
			ft_free_tab(command);	
		}
		free(command);
	}
	free(input);
	return (0);
}
