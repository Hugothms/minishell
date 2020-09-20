/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:58 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/20 19:43:26 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(void)
{
	char	*ret;
	char	*tmp;

	ret = getcwd(NULL, 0);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	free(tmp);
	return(ret);
}

char	*ft_echo(char **args)
{
	int		i;
	int		nflag;
	char	*ret;
	char	*tmp;

	nflag = 0;
	ret = malloc(sizeof(char));
	*ret = '\0';
	if (!*args)
		return (ret);
	i = 0;
	while (!ft_strcmp(args[i], "-n"))
	{
		nflag = 1;
		i++;
	}
	while(args[i])
	{
		tmp = ret;
		ret = ft_strjoin(ret, args[i]);
		free(tmp);
		if (args[i + 1])
		{
			tmp = ret;
			ret = ft_strjoin(ret, " ");
			free(tmp);
		}		
		i++;
	}
	if(!nflag)
	{
		tmp = ret;
		ret = ft_strjoin(ret, "\n");
		free(tmp);
	}
	return (ret);
}

char	*ft_cd(char **args)
{
	char		*ret;
	char		*tmp;	
	struct stat	stats;

	if (!*args)
		chdir("/");
    if (stat(*args, &stats) != 0)
    {
		ret = ft_strdup("cd: no such file or directory: ");
		tmp = ret;
		ret = ft_strjoin(ret, *args);
		free(tmp);
		tmp = ret;
		ret = ft_strjoin(ret, "\n");
		free(tmp);
		return(ret);
	}
	else
		if(chdir(*args))
		{
			ret = (ft_strdup("cd: not a directory: "));
			tmp = ret;
			ret = ft_strjoin(ret, *args);
			free(tmp);
			tmp = ret;
			ret = ft_strjoin(ret, "\n");
			free(tmp);
			return(ret);
		}
	return(ft_strdup(""));
}

char	*ft_env(char **args)
{
	return(NULL);
}

char	*ft_exit(char **args)
{
	if(*args)
	{	
		if (ft_isdigit(**args))
			exit(**args - '0');
	}
	exit(0);
	return(NULL);
}

char	*ft_export(char **args)
{
	return(NULL);
}

char	*ft_unset(char **args)
{
	return(NULL);
}


// echo		with option ’-n’
// cd		with only a relative or absolute path
// pwd		without any options
//! export	without any options
//! unset	without any options
//! env		without any options and any arguments
// exit		without any options
