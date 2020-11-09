/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:31 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/09 12:08:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env(t_list *env, int *exit_status)
{
	char	*ret;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while (env)
	{
		ret = ft_strjoin_free(ret, env->content);
		ret = ft_strjoin_free(ret, "\n");
		env = env->next;
	}
	return (ret);
}
