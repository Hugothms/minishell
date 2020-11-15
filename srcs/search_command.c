/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:04:47 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/15 15:09:35 by hthomas          ###   ########.fr       */
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

void	binary_not_found(char *path, int *ret, int *exit_status)
{
	struct stat	buf;
	int			dir;

	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	dir = lstat(path, &buf);
	printf(" %08x ", buf.st_mode);
	if (dir == 0)
	{
		if (buf.st_mode /*== S_ISDIR*/)
		{
			ft_putstr_fd(": is a directory\n", STDERR);
			*exit_status = 126;
		}
		else
		{
			ft_putstr_fd(": permission denied\n", STDERR);
			*exit_status = 126;
		}
	}
	else
	{
		ft_putstr_fd(": no such file or directory\n", STDERR);
		*exit_status = 127;
	}
	*ret = FAILURE;
}

void	try_path(t_list_cmd *cmd, char **envp, char **argv, int *ret, int *exit_status)
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
		binary_not_found(cmd->str, ret, exit_status);
}

int		execute_command(t_list_cmd *cmd, char **envp, int *exit_status)
{
	int		ret;
	char	**argv;

	ret = FAILURE;
	if (!(argv = lst_to_strs(cmd)))
		return (FAILURE);
	if (cmd->str[0] == '/')
	{
		if (execve(cmd->str, argv, envp))
			binary_not_found(cmd->str, &ret, exit_status);
	}
	else if (cmd->str[0] == '.' && cmd->str[1] == '/')
	{
		if (execve(cmd->str, argv, envp))
			binary_not_found(cmd->str, &ret, exit_status);
	}
	else
		try_path(cmd, envp, argv, &ret, exit_status);
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
		if (execute_command(cmd, envp, exit_status))
			exit(*exit_status);
	}
	else
	{
		wait(exit_status);
		*exit_status = *exit_status >> 8;
		ret = FAILURE;
	}
	ft_free_tab(envp);
	return (ret);
}
