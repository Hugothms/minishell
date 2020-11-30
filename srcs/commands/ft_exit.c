/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:34 by vmoreau           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/11/29 14:12:54 by vmoreau          ###   ########.fr       */
=======
/*   Updated: 2020/11/29 18:57:17 by hthomas          ###   ########.fr       */
>>>>>>> 8bb4b3d7bd7a7798f02a6202b541442667359e40
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
<<<<<<< HEAD
	if (args)
	{
		if ((err = ft_atoi_strict(args->str)))
		{
			g_glob.exit = err;
			exit(g_glob.exit);
		}
	}
=======
	if (args && (err = ft_atoi_strict(args->str)))
		g_glob.exit = err;
>>>>>>> 8bb4b3d7bd7a7798f02a6202b541442667359e40
	exit(g_glob.exit);
	return (NULL);
}
