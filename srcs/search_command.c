/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 13:09:04 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = ft_split(&envp[i][5], ':');
	return (path);
}

char	**lst_to_strs(t_list_command *command)
{
	char	**argv;
	int		i;

	if(!(argv = malloc(sizeof(*argv) * (c_lstsize(command) + 1))))
		return (NULL);
	i = 0;
	while (command)
	{
		argv[i++] = ft_strdup(command->str);
		command = command->next;
	}
	argv[i] = NULL;
	return (argv);
}

int		try_path(t_list_command *command, char **envp)
{
	int		i;
	int		cpt;
	int		ret;
	char	**path;
	char	*full_path;
	char	**argv;

	path = get_paths(envp);
	i = 0;
	cpt = 0;
	ret = 1;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], "/");
		full_path = ft_strjoin_free(full_path, command->str);
		if (argv = lst_to_strs(command))
		{
			if (execve(full_path, argv, envp))
				cpt++;
			ft_free_tab(argv);
		}
		free(full_path);
		if (i != cpt)
			ret = 0;
		i++;
	}
	ft_free_tab(path);
	return (ret);
}

int		search_command(t_list_command *command, char **envp)
{
	int	ret;

	ret = 1;
	pid_t pid = fork();
	if (pid == 0)
	{
		if (try_path(command, envp))
			exit(0);
	}
	else
	{
		ret = 0;
		wait(0);
	}
	return (ret);
}