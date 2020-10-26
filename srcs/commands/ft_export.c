/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:36 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/26 20:05:23 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**duptab(t_list *envp)
{
	//char	**dubtab;
	//int		i;

	//i = 0;
	//while (envp[i])
	//	i++;
	//dubtab = (char **)malloc(sizeof(char *) * (i + 1));
	//i = 0;
	//while (envp[i])
	//{
	//	dubtab[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 3));
	//	ft_strcpy(dubtab[i], envp[i]);
	//	dubtab[i][ft_strlen(envp[i])] = '#';
	//	dubtab[i][ft_strlen(envp[i]) + 1] = '\"';
	//	dubtab[i][ft_strlen(envp[i]) + 2] = '\0';
	//	i++;
	//}
	//dubtab[i] = NULL;
	//return (dubtab);
}

char	*ft_export_no_arg(t_list *envp)
{
	//char	*ret;
	//char	**tri;
	//int		i;

	//i = 0;
	//tri = duptab(envp);
	//sort(tri);
	//add_quote(tri);
	//ret = ft_strdup("");
	//while (tri[i])
	//{
	//	ret = ft_strjoin_free(ret, "declare -x ");
	//	ret = ft_strjoin_free(ret, tri[i++]);
	//	ret = ft_strjoin_free(ret, "\n");
	//}
	//ft_free_tab(tri);
	//return(ret);
}

char	*ft_export(t_list_cmd *args, t_list *envp)
{
	//char	*key;
	//char	*value;
	//int		equal_pos;
	//int		i;
	//int		bool;

	//if (!args || !args->str)
	//	return (ft_export_no_arg(envp));
	//while (args)
	//{
	//	equal_pos = 0;
	//	while (args->str[equal_pos] && args->str[equal_pos] != '=')
	//		equal_pos++;
	//	key = ft_strndup(args->str, equal_pos);
	//	if (args->str[equal_pos] == '=')
	//		value = ft_strdup(&(args->str[equal_pos + 1]));
	//	else
	//		value = ft_strdup("");
	//	i = 0;
	//	while (envp[i])
	//	{
	//		bool = 0;
	//		if (!ft_strncmp(envp[i], key, ft_strlen(key))
	//			&& args->str[equal_pos] == '=')
	//		{
	//			bool = 1;
	//			free(envp[i]);
	//			envp[i] = ft_strjoin_free(key, "=");
	//			envp[i] = ft_strjoin_free(envp[i], value);
	//			free(value);
	//			break;
	//		}
	//		i++;
	//	}
	//	if (args->str[equal_pos] == '=' && bool == 0)
	//	{
	//		envp[i] = ft_strjoin_free(key, "=");
	//		envp[i] = ft_strjoin_free(envp[i], value);
	//		envp[i + 1] = NULL;
	//		free(value);
	//	}
	//	args = args->next;
	//}
	//return(ft_strdup(""));
}

char	*ft_export2(t_list_cmd *args, char **envp)
{
	//char	*key;
	//char	*value;
	//int		equal_pos;
	//int		i;

	//if (!args || !args->str)
	//	return (ft_export_no_arg(envp));

	//equal_pos = 0;

	//while (args->str[equal_pos] && args->str[equal_pos] != '=')
	//	equal_pos++;

	//key = ft_strndup(args->str, equal_pos);
	//value = ft_strdup(&(args->str[equal_pos + 1]));
	//i = 0;

	//while (envp[i])
	//{
	//	if (!ft_strncmp(envp[i], key, ft_strlen(key)))
	//	{
	//		envp[i] = ft_strjoin_free(key, "=");
	//		envp[i] = ft_strjoin_free(envp[i], value);
	//		free(value);
	//		return (ft_strdup(""));
	//	}
	//	i++;
	//}
	
	//envp[i] = ft_strjoin_free(key, "=");
	//envp[i] = ft_strjoin_free(envp[i], value);
	//free(value);
	//envp[i + 1] = NULL;
	//return (ft_strdup(""));
}