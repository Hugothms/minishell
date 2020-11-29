/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:34 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/29 12:01:06 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_env_lst(t_list *env)
{
	if (!env)
		return ;
	if (env->next)
		clear_env_lst(env->next);
	free(env->content);
	free(env);
	env = NULL;
}

char	*ft_exit(t_list_cmd *args, t_list *env)
{
	int	err;

	clear_env_lst(env);
	free(g_glob.path);
	if (args)
	{
		if ((err = ft_atoi_strict(args->str)))
		{
			g_glob.exit = err;
			exit(g_glob.exit);
		}
	}
	// g_glob.exit = 0;
	exit(g_glob.exit);
	return (NULL);
}
