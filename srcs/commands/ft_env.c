/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:31 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/09 11:57:10 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env(t_list *envp, int *exit_status)
{
	char	*ret;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while (envp)
	{
		ret = ft_strjoin_free(ret, envp->content);
		ret = ft_strjoin_free(ret, "\n");
		envp = envp->next;
	}
	return (ret);
}
