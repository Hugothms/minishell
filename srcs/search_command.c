/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/08 14:53:56 by hthomas          ###   ########.fr       */
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

char	**lst_to_strs(t_list_cmd *cmd)
{
	char	**argv;
	int		i;

	if (!(argv = malloc(sizeof(*argv) * (c_lst_size(cmd) + 1))))
		return (NULL);
	i = 0;
	while (cmd)
	{
		argv[i++] = ft_strdup(cmd->str);
		cmd = cmd->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	try_path2(t_list_cmd *cmd, char **envp, char *begin, int *cpt)
{
	char	*full_path;
	char	**argv;

	full_path = ft_strjoin(begin, "/");
	full_path = ft_strjoin_free(full_path, cmd->str);
	if (argv = lst_to_strs(cmd))
	{
		if (execve(full_path, argv, envp))
			*cpt++;
		ft_free_tab(argv);
	}
	free(full_path);
}

int		try_path(t_list_cmd *cmd, char **envp)
{
	int		i;
	int		cpt;
	int		ret;
	char	**path;

	path = get_paths(envp);
	i = 0;
	cpt = 0;
	ret = ERR;
	while (path[i])
	{
		try_path2(cmd, envp, path[i], &cpt);
		if (i != cpt)
			ret = OK;
		i++;
	}
	ft_free_tab(path);
	return (ret);
}

int		search_command(t_list_cmd *cmd, char **envp)
{
	int		ret;
	int		status;
	pid_t	pid;

	ret = ERR;
	pid = fork();
	if (pid == 0)
	{
		if (try_path(cmd, envp))
			exit(0);
	}
	else
	{
		ret = OK;
		wait(&status);
	}
	return (ret);
}
