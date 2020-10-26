/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:41 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/22 16:25:51 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_unset(t_list_cmd *args, char **envp)
{
	char	*var;
	char	**tmp;
	int		i;

	if (!args || !args->str)
		return (ft_strdup(""));
	tmp = ft_split(args->str, '=');
	var = ft_strdup(*tmp);
	ft_free_tab(tmp);
	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp(envp[i], var))
		{
			envp[i][ft_strlen(var)] = '\0';
			break ;
		}
		i++;
	}
	free(var);
	return (ft_strdup(""));
}