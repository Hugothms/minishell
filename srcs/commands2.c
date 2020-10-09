/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 23:09:57 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 11:22:48 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env(t_list *args, char **envp)
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

char	*ft_export(t_list *args, char **envp)
{
	char	*key;
	char	*value;
	int		equal_pos;
	int		i;

	if (!args || !((t_word*)args->content)->str)
		return (ft_env(args, envp));
	equal_pos = 0;
	while (((t_word*)args->content)->str[equal_pos] && ((t_word*)args->content)->str[equal_pos] != '=')
		equal_pos++;
	if (equal_pos == ft_strlen(((t_word*)args->content)->str) && ((t_word*)args->content)->str[equal_pos] != '=')
		return (NULL);
	key = ft_strndup(((t_word*)args->content)->str, equal_pos);
	value = ft_strdup(&(((t_word*)args->content)->str[equal_pos + 1]));
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

char	*ft_unset(t_list *args, char **envp)
{
	char	*var;
	char	**tmp;
	int		i;

	if (!args || !((t_word*)args->content)->str)
		return (ft_strdup(""));
	tmp = ft_split(((t_word*)args->content)->str, '=');
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
