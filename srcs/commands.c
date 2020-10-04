/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:58 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 15:36:09 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	ret = ft_strjoin_free(ret, "\n");
	return (ret);
}

char	*ft_echo(t_list_command *args)
{
	int		nflag;
	char	*ret;

	nflag = 0;
	if (!args || !args->str)
		return (ft_strdup("\n"));
	while (!ft_strcmp(args->str, "-n"))
	{
		nflag = 1;
		args = args->next;
	}
	ret = ft_strdup("");
	while (args)
	{
		ret = ft_strjoin_free(ret, args->str);
		if (args->next && !(args->flags & NO_SPACE_AFTER))
			ret = ft_strjoin_free(ret, " ");
		args = args->next;
	}
	if (!nflag)
		ret = ft_strjoin_free(ret, "\n");
	return (ret);
}

char	*find_var_env(char **envp, char *var)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_cd(t_list_command *args, char **envp)
{
	char		*ret;
	struct stat	stats;

	if (!args || !args->str)
		chdir(&find_var_env(envp, "HOME=")[5]);  
    else if (stat(args->str, &stats) != 0)
    {
		ret = ft_strdup("cd: no such file or directory: ");
		ret = ft_strjoin_free(ret, args->str);
		ret = ft_strjoin_free(ret, "\n");
		return (ret);
	}
	else
		if (chdir(args->str))
		{
			ret = (ft_strdup("cd: not a directory: "));
			ret = ft_strjoin_free(ret, args->str);
			ret = ft_strjoin_free(ret, "\n");
			return (ret);
		}
	return (ft_strdup(""));
}

char	*ft_env(t_list_command *args, char **envp)
{
	char	*ret;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while (envp[i])
	{
		ret = ft_strjoin_free(ret, envp[i++]);
		ret = ft_strjoin_free(ret, "\n");
	}
	return (ret);
}

char	*ft_export(t_list_command *args, char **envp)
{
	char	*key;
	char	*value;
	int		equal_pos;
	int		i;

	if (!args || !args->str)
		return (ft_env(args, envp));
	equal_pos = 0;
	while (args->str[equal_pos] && args->str[equal_pos] != '=')
		equal_pos++;
	if (equal_pos == ft_strlen(args->str) && args->str[equal_pos] != '=')
		return (NULL);
	key = ft_strndup(args->str, equal_pos);
	value = ft_strdup(&(args->str[equal_pos + 1]));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			envp[i] = ft_strjoin_free(key, "=");
			envp[i] = ft_strjoin_free(envp[i], value);
			free(value);
			return (ft_strdup(""));
		}
		i++;
	}
	envp[i] = ft_strjoin_free(key, "=");
	envp[i] = ft_strjoin_free(envp[i], value);
	free(value);
	envp[i + 1] = NULL;
	return (ft_strdup(""));
}

char	*ft_unset(t_list_command *args, char **envp)
{
	char	*var;
	char	**tmp;
	int		i;

	if (!args || !args->str)
		return (ft_strdup(""));
	tmp = ft_split(args->str, '=');
	var = ft_strdup(*tmp);
	ft_free_tab(tmp);
	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp(envp[i], var))
		{
			envp[i][ft_strlen(var)] = '\0';
			break ;
		}
		i++;
	}
	free(var);
	return (ft_strdup(""));
}

char	*ft_exit(t_list_command *args)
{
	int	err;
	
	if (args)
	{	
		if (err = ft_atoi(args->str))
			exit(err);
	}
	exit(0);
	return (NULL);
}


// echo	with option ’-n’
// cd		with only a relative or absolute path
// pwd		without any options
//! export	without any options
//! unset	without any options
//! env		without any options and any arguments
// exit		without any options
