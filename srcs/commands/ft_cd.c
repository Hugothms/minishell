/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:24 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/18 16:28:25 by vmoreau          ###   ########.fr       */
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

char	*error_cd(char *arg, int err_status)
{
	char *ret;

	g_glob.exit = 1;
	ret = ft_strdup("minishell: cd: ");
	if (err_status > 0)
		ret = ft_strjoin_free(ret, arg);
	if (err_status == 0)
		ret = ft_strjoin_free(ret, "To many arguments");
	else if (err_status == 1)
		ret = ft_strjoin_free(ret, ": No such file or directory");
	else if (err_status == 2)
		ret = ft_strjoin_free(ret, ": Not a directory");
	else if (err_status == 3)
		ret = ft_strjoin_free(ret, " Not set");

	ret = ft_strjoin_free(ret, "\n");
	return (ret);
}

char	*cd_oldpwd(t_list *env, t_list_cmd *arg, struct stat *stats)
{
	char *path;
	char *ret;

	if (find_var_env(env, "OLDPWD=") && find_var_env(env, "OLDPWD=")[7] != '\0')
	{
		path = ft_strdup(&find_var_env(env, "OLDPWD=")[7]);
		if (stat(path, stats) != 0)
			return (error_cd(path, 1));
		else if (chdir(path))
			return (error_cd(path, 2));
		modif_oldpwd_pwd(env);
		ret = ft_strjoin_free(path, "\n");
	}
	else
	{
		ret = ft_strdup("minishell: cd: OLDPWD not set\n");
		g_glob.exit = 1;
	}
	return (ret);
}

char	*ft_cd(t_list_cmd *args, t_list *env)
{
	char		*ret;
	struct stat	stats;

	g_glob.exit = 0;
	if (!args || !args->str)
	{
		if (chdir(&find_var_env(env, "HOME=")[5]))
			return (error_cd("« HOME »", 3));
	}
	else if (c_lst_size(args) > 1)
		return (error_cd(args->str, 0));
	else if (!ft_strcmp(args->str, "-"))
		return (cd_oldpwd(env, args, &stats));
	else if (stat(args->str, &stats) != 0)
		return (error_cd(args->str, 1));
	else if (chdir(args->str))
		return (error_cd(args->str, 2));
	modif_oldpwd_pwd(env);
	return (ft_strdup(""));
}
