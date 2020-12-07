/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:15:00 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/07 15:17:15 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**lst_to_chartab(t_list *env)
{
	char	**ret;
	int		i;

	if (!(ret = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		ret[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	modif_var_env(t_list *env, char *key, char *new_value)
{
	while (env)
	{
		if (!ft_strncmp(env->content, key, ft_strlen(key)))
		{
			free(env->content);
			env->content = ft_strjoin(key, "=");
			env->content = ft_strjoin_free(env->content, new_value);
		}
		env = env->next;
	}
}

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
