/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:58 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 11:22:49 by hthomas          ###   ########.fr       */
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

char	*ft_echo(t_list *args)
{
	int		nflag;
	char	*ret;

	nflag = 0;
	if (!args || !((t_word*)args->content)->str)
		return (ft_strdup("\n"));
	while (!ft_strcmp(((t_word*)args->content)->str, "-n"))
	{
		nflag = 1;
		args = args->next;
	}
	ret = ft_strdup("");
	while (args)
	{
		ret = ft_strjoin_free(ret, ((t_word*)args->content)->str);
		if (args->next && !(((t_word*)args->content)->flags & NO_SPACE_AFTER))
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
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_cd(t_list *args, char **envp)
{
	char		*ret;
	struct stat	stats;

	if (!args || !((t_word*)args->content)->str)
		chdir(&find_var_env(envp, "HOME=")[5]);
	else if (stat(((t_word*)args->content)->str, &stats) != 0)
	{
		ret = ft_strdup("cd: no such file or directory: ");
		ret = ft_strjoin_free(ret, ((t_word*)args->content)->str);
		ret = ft_strjoin_free(ret, "\n");
		return (ret);
	}
	else if (chdir(((t_word*)args->content)->str))
	{
		ret = (ft_strdup("cd: not a directory: "));
		ret = ft_strjoin_free(ret, ((t_word*)args->content)->str);
		ret = ft_strjoin_free(ret, "\n");
		return (ret);
	}
	return (ft_strdup(""));
}

char	*ft_exit(t_list *args)
{
	int	err;

	if (args)
	{
		if (err = ft_atoi(((t_word*)args->content)->str))
			exit(err);
	}
	exit(0);
	return (NULL);
}
