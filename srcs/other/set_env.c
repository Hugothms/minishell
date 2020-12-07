/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:46:21 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/07 14:46:34 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_env(t_list **env)
{
	char	*keyval;
	char	*pwd;

	keyval = ft_strdup("SHLVL=0");
	ft_lstadd_back(env, ft_lstnew(keyval));
	pwd = getcwd(NULL, 0);
	keyval = ft_strjoin("PWD=", pwd);
	free(pwd);
	ft_lstadd_back(env, ft_lstnew(keyval));
	keyval = ft_strdup("OLDPWD=");
	ft_lstadd_back(env, ft_lstnew(keyval));
}

void	set_env(char **envp, t_list **env)
{
	int		i;
	char	*keyval;

	i = 0;
	*env = NULL;
	if (envp[i])
	{
		while (envp[i])
		{
			keyval = ft_strdup(envp[i]);
			ft_lstadd_back(env, ft_lstnew(keyval));
			i++;
		}
	}
	else
		fill_env(env);
}
