/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:58 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/25 12:07:12 by hthomas          ###   ########.fr       */
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

char	*ft_echo(char **args)
{
	int		i;
	int		nflag;
	char	*ret;

	nflag = 0;
	if (!*args)
		return (ft_strdup("\n"));
	i = 0;
	while (!ft_strcmp(args[i], "-n"))
	{
		nflag = 1;
		i++;
	}
	ret = ft_strdup("");
	while (args[i])
	{
		ret = ft_strjoin_free(ret, args[i]);
		if (args[i + 1])
			ret = ft_strjoin_free(ret, " ");
		i++;
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

char	*ft_cd(char **args, char **envp)
{
	char		*ret;
	struct stat	stats;

	if (!*args)
		chdir(&find_var_env(envp, "HOME=")[5]);  
    if (stat(*args, &stats) != 0)
    {
		ret = ft_strdup("cd: no such file or directory: ");
		ret = ft_strjoin_free(ret, *args);
		ret = ft_strjoin_free(ret, "\n");
		return (ret);
	}
	else
		if (chdir(*args))
		{
			ret = (ft_strdup("cd: not a directory: "));
			ret = ft_strjoin_free(ret, *args);
			ret = ft_strjoin_free(ret, "\n");
			return (ret);
		}
	return (ft_strdup(""));
}

char	*ft_env(char **args, char **envp)
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

char	*ft_export(char **args, char **envp)
{
	char	*var;
	char	**tmp;
	int		equal_pos;
	int		i;

	if (!*args)
		return (ft_env(args,envp));
	equal_pos = 0;
	while ((*args)[equal_pos] && (*args)[equal_pos] != '=')
		equal_pos++;
	if (equal_pos != ft_strlen(*args))
		
		
	tmp = ft_split(*args, '=');
	var = ft_strdup(*tmp);
	ft_free_tab(tmp);
	free(tmp);
	i = 0;
	while (envp[i])
	{
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_unset(char **args, char **envp)
{
	char	*var;
	char	**tmp;
	int		i;

	if (!*args)
		return (ft_strdup(""));
	tmp = ft_split(*args, '=');
	var = ft_strdup(*tmp);
	ft_free_tab(tmp);
	free(tmp);
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

char	*ft_exit(char **args)
{
	if (*args)
	{	
		if (ft_isdigit(**args))
			exit(**args - '0');
	}
	exit(0);
	return (NULL);
}


// echo	with option ’-n’ //!and $VAR
// cd		with only a relative or absolute path
// pwd		without any options
//! export	without any options
//! unset	without any options
//! env		without any options and any arguments
// exit		without any options
