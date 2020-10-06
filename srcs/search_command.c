/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/06 23:32:14 by hthomas          ###   ########.fr       */
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

	if (!(argv = malloc(sizeof(*argv) * (c_lst_size(command) + 1))))
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

void	try_path2(t_list_command *command, char **envp, char *begin, int *cpt)
{
	char	*full_path;
	char	**argv;

	full_path = ft_strjoin(begin, "/");
	full_path = ft_strjoin_free(full_path, command->str);
	if (argv = lst_to_strs(command))
	{
		if (execve(full_path, argv, envp))
			*cpt++;
		ft_free_tab(argv);
	}
	free(full_path);
}

int		try_path(t_list_command *command, char **envp)
{
	int		i;
	int		cpt;
	int		ret;
	char	**path;

	path = get_paths(envp);
	i = 0;
	cpt = 0;
	ret = 1;
	while (path[i])
	{
		try_path2(command, envp, path[i], &cpt);
		if (i != cpt)
			ret = 0;
		i++;
	}
	ft_free_tab(path);
	return (ret);
}

int		search_command(t_list_command *command, char **envp)
{
	int		ret;
	int		status;
	pid_t	pid;

	ret = 1;
	pid = fork();
	if (pid == 0)
	{
		if (try_path(command, envp))
			exit(0);
	}
	else
	{
		ret = 0;
		wait(&status);
	}
	return (ret);
}
