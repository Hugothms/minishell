/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:34 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/28 15:02:55 by vmoreau          ###   ########.fr       */
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
	if (args)
	{
		if ((err = ft_atoi(args->str)))
			exit(err);
	}
	exit(0);
	return (NULL);
}
