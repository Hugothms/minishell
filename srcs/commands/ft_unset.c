/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:41 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/09 12:09:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char	**catch_arg(t_list_cmd *args)
{
	char	**ret;
	int		i;

	i = c_lst_size(args);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args)
	{
		ret[i] = ft_strdup(args->str);
		args = args->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	lst_del_next_node(t_list *env)
{
	t_list	*tmp;

	if (!env || !env->next)
		return ;
	tmp = env->next->next;
	free(env->next->content);
	free(env->next);
	env->next == NULL;
	env->next = tmp;
}

char	*ft_unset(t_list_cmd *args, t_list *env, int *exit_status)
{
	char	**var;
	int		i;

	if (!args || !args->str)
		return (ft_strdup(""));
	var = catch_arg(args);
	i = 0;
	while (var[i])
	{
		while (env->next)
		{
			if (!ft_strncmp(env->next->content, var[i], ft_strlen(var[i])))
			{
				lst_del_next_node(env);
				break ;
			}
			env = env->next;
		}
		i++;
	}
	ft_free_tab(var);
	return (ft_strdup(""));
}
