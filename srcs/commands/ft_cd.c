/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:24 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/09 12:08:03 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_var_env(t_list *env, char *var)
{
	while (env)
	{
		if (!ft_strncmp(env->content, var, ft_strlen(var)))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

void	modif_oldpwd_pwd(t_list *env)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	modif_var_env(env, "OLDPWD", &find_var_env(env, "PWD=")[4]);
	modif_var_env(env, "PWD", pwd);
	free(pwd);
}

char	*ft_cd(t_list_cmd *args, t_list *env, int *exit_status)
{
	char		*ret;
	struct stat	stats;

	if (!args || !args->str)
		chdir(&find_var_env(env, "HOME=")[5]);
	else if (stat(args->str, &stats) != 0)
	{
		*exit_status = 1;
		ret = ft_strdup("cd: no such file or directory: ");
		ret = ft_strjoin_free(ret, args->str);
		ret = ft_strjoin_free(ret, "\n");
		return (ret);
	}
	else if (chdir(args->str))
	{
		*exit_status = 1;
		ret = (ft_strdup("cd: not a directory: "));
		ret = ft_strjoin_free(ret, args->str);
		ret = ft_strjoin_free(ret, "\n");
		return (ret);
	}
	modif_oldpwd_pwd(env);
	return (ft_strdup(""));
}
