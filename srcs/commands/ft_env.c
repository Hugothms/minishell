/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:31 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/16 14:12:37 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env(t_list *env)
{
	char	*ret;
	int		i;

	g_glob.exit = 0;
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
