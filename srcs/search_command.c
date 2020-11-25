/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/24 14:46:39 by vmoreau          ###   ########.fr       */
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

	dir = lstat(path, &buf);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (dir == 0)
	{
		g_glob.exit = 126;
		if (buf.st_mode > 32768 && buf.st_mode < 33215)
			ft_putstr_fd(": Permission denied\n", STDERR);
		else
			ft_putstr_fd(": is a directory\n", STDERR);
	}
	else
	{
		ft_putstr_fd(": no such file or directory\n", STDERR);
		g_glob.exit = 127;
	}
	*ret = FAILURE;
}

void	try_path2(t_list_cmd *cmd, char **envp, char **argv, int *ret)
{
	int		i;
	int		cpt;
	char	**path;
	char	*full_path;

	path = get_paths(envp);
	if (path != NULL)
	{
		i = 0;
		cpt = 0;
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

int		try_path(t_list_cmd *cmd, char **envp)
{
	int		ret;
	char	**argv;

	ret = FAILURE;
	if (!(argv = cmd_to_strs(cmd)))
		return (FAILURE);
	if (cmd->str[0] == '/')
	{
		if (execve(cmd->str, argv, envp))
			binary_not_found(cmd->str, &ret);
	}
	else if (cmd->str[0] == '.' && cmd->str[1] == '/')
	{
		if (execve(cmd->str, argv, envp))
			binary_not_found(cmd->str, &ret);
	}
	else
		try_path2(cmd, envp, argv, &ret);
	ft_free_tab(argv);
	return (ret);
}

int		search_command(t_list_cmd *cmd, t_list *env)
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
		if (try_path(cmd, envp))
			exit(g_glob.exit);
	}
	else
	{
		wait(&g_glob.exit);
		g_glob.exit = g_glob.exit >> 8;
		ret = FAILURE;
	}
	ft_free_tab(envp);
	return (ret);
}
