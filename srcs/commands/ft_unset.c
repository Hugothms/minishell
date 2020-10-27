/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:41 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/26 20:04:30 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char **catch_arg(t_list_cmd *args)
{
	char **ret;
	int i;

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
	return(ret);
}

//void sort(char **tri)
//{
//	char *tmp;
//	int i;
//	int j;

//	i = 0;
//	j = 1;
//	while (tri[i + 1] != NULL)
//	{
//		if (ft_strcmp(tri[i], tri[j]) > 0)
//		{
//			tmp = tri[j];
//			tri[j] = tri[i];
//			tri[i] = tmp;
//			j = i + 1;
//		}
//		else if (tri[j + 1] == NULL)
//		{
//			i++;
//			j = i + 1;
//		}
//		else
//			j++;
//	}
//}

char	*ft_unset(t_list_cmd *args, t_list *envp)
{
	//char	**var;
	//int		i;
	//int		j;

	//if (!args || !args->str)
	//	return (ft_strdup(""));
	////sort(envp);
	//var = catch_arg(args);
	//i = 0;
	//while (var[i])
	//{
	//	j = 0;
	//	while (envp[j])
	//	{
	//		if (!ft_strncmp(envp[j], var[i], ft_strlen(var[i])))
	//		{
	//			envp[j] = NULL;
	//			break ;
	//		}
	//		j++;
	//	}
	//	i++;
	//}
	//ft_free_tab(var);
	//return (ft_strdup(""));
}
