/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/02 15:28:28 by hthomas          ###   ########.fr       */
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

int		try_path(t_list_command *command, char **envp, t_execve exec)
{
	int		i;
	int		cpt;
	int		ret;
	char	**path;
	char	*full_path;

	path = get_path(envp);
	i = 0;
	cpt = 0;
	ret = 1;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], "/");
		full_path = ft_strjoin_free(full_path, command->str);
		if (execve(full_path, command, exec.envp))
			cpt++;
		free(full_path);
		if (i != cpt)
			ret = 0;
		i++;
	}
	ft_free_tab(path);
	free(path);
	return (ret);
}

int		search_command(t_list_command *command, char **envp, t_execve exec)
{
	int	ret;

	ret = 1;
	pid_t pid = fork();
	if (pid == 0)
	{
		if (try_path(command, envp, exec))
			exit(0);
	}
	else
	{
		ret = 0;
		wait(0);
	}
	return (ret);
}