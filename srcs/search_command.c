/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/13 14:26:09 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i] != NULL)
		path = ft_split(&envp[i][5], ':');
	return (path);
}

void	binary_not_found(char *path, int *ret)
{
	struct stat	buf;
	int			dir;

	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	dir = lstat(path, &buf);
	if (dir == 0)
		ft_putstr_fd(": Is a directory\n", STDERR);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR);
	*ret = FAILURE;
}

void	try_path2(t_list_cmd *cmd, char **envp, char **argv, int *ret)
{
	int		i;
	int		cpt;
	char	**path;
	char	*full_path;

	i = 0;
	cpt = 0;
	path = get_paths(envp);
	if (path != NULL)
	{
		while (path[i])
		{
			full_path = ft_strjoin(path[i], "/");
			full_path = ft_strjoin_free(full_path, cmd->str);
			if (execve(full_path, argv, envp))
				cpt++;
			free(full_path);
			if (i != cpt)
				*ret = SUCCESS;
			i++;
		}
		ft_free_tab(path);
	}
	else
		binary_not_found(cmd->str, ret);
}

int		try_path(t_list_cmd *cmd, char **envp, int *exit_status)
{
	int		ret;
	char	**argv;

	ret = FAILURE;
	if (!(argv = lst_to_strs(cmd)))
		return (FAILURE);
	if (cmd->str[0] == '/' || cmd->str[0] == '.')
	{
		if (execve(cmd->str, argv, envp))
			binary_not_found(cmd->str, &ret);
	}
	else
		try_path2(cmd, envp, argv, &ret);
	ft_free_tab(argv);
	return (ret);
}

int		search_command(t_list_cmd *cmd, t_list *env, int *exit_status)
{
	int		ret;
	int		status;
	pid_t	pid;
	char	**envp;

	ret = SUCCESS;
	pid = fork();
	envp = lst_to_chartab(env);
	if (pid == 0)
	{
		if (try_path(cmd, envp, exit_status))
			exit(0);
	}
	else
	{
		wait(&status);
		*exit_status = 0;
		ret = FAILURE;
	}
	ft_free_tab(envp);
	return (ret);
}
