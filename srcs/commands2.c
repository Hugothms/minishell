/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 23:09:57 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/22 14:28:58 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env(char **envp)
{
	char	*ret;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while (envp[i])
	{
		ret = ft_strjoin_free(ret, envp[i++]);
		ret = ft_strjoin_free(ret, "\n");
	}
	return (ret);
}

void sort(char **tri)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 1;
	while (tri[i + 1] != NULL)
	{
		if (ft_strcmp(tri[i], tri[j]) > 0)
		{
			tmp = tri[j];
			tri[j] = tri[i];
			tri[i] = tmp;
			j = i + 1;
		}
		else if (tri[j + 1] == NULL)
		{
			i++;
			j = i + 1;
		}
		else
			j++;
	}
}

char	*ft_export_no_arg(char **envp)
{
	char	*ret;
	char	**tri;
	int		i;

	i = 0;
	tri = envp;
	sort(tri);
	ret = ft_strdup("");
	while (tri[i])
	{
		ret = ft_strjoin_free(ret, "declare -x ");
		ret = ft_strjoin_free(ret, tri[i++]);
		ret = ft_strjoin_free(ret, "\n");
	}
	return(ret);
}

char	*ft_export(t_list_cmd *args, char **envp)
{
	char	*key;
	char	*value;
	int		equal_pos;
	int		i;

	if (!args || !args->str)
		return (ft_export_no_arg(envp));
	equal_pos = 0;
	while (args->str[equal_pos] && args->str[equal_pos] != '=')
		equal_pos++;
	if (equal_pos == ft_strlen(args->str) && args->str[equal_pos] != '=')
		return (NULL);
	key = ft_strndup(args->str, equal_pos);
	value = ft_strdup(&(args->str[equal_pos + 1]));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key)))
		{
			envp[i] = ft_strjoin_free(key, "=");
			envp[i] = ft_strjoin_free(envp[i], value);
			free(value);
			return (ft_strdup(""));
		}
		i++;
	}
	envp[i] = ft_strjoin_free(key, "=");
	envp[i] = ft_strjoin_free(envp[i], value);
	free(value);
	envp[i + 1] = NULL;
	return (ft_strdup(""));
}

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
