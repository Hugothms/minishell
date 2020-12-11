/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:41 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/11 16:14:17 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

static char	**catch_arg(t_list_cmd *args)
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

static void	lst_del_next_node(t_list *env, char *var)
{
	t_list	*tmp;

	if (!env || !env->next)
		return ;
	while (env->next)
	{
		if (!ft_strncmp(env->next->content, var, ft_strlen(var)))
		{
			tmp = env->next->next;
			free(env->next->content);
			free(env->next);
			env->next == NULL;
			env->next = tmp;
			break ;
		}
		env = env->next;
	}
}

char		*ft_unset(t_list_cmd *args, t_list *env)
{
	char	**var;
	int		i;

	g_glob.exit = 0;
	if (!args || !args->str || (args->flags == 512 && args->str[0] == '\0'))
		return (ft_strdup(""));
	var = catch_arg(args);
	i = 0;
	while (var[i])
	{
		if (ft_isalpha(var[i][0]))
			lst_del_next_node(env, var[i]);
		else
		{
			g_glob.exit = 1;
			ft_putstr_fd("minishell: unset: « ", STDERR);
			ft_putstr_fd(var[i], STDERR);
			ft_putstr_fd(" » : not valid identifier\n", STDERR);
		}
		i++;
	}
	ft_free_tab(var);
	return (ft_strdup(""));
}
