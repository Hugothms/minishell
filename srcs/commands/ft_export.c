/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:36 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/27 15:54:49 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**duptab(t_list *envp)
{
	char	**dubtab;
	int		i;

	i = ft_lstsize(envp);
	dubtab = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp)
	{
		dubtab[i] = malloc(sizeof(char) * (ft_strlen(envp->content) + 3));
		ft_strcpy(dubtab[i], envp->content);
		if (have_egual(envp->content))
			dubtab[i][ft_strlen(envp->content)] = '#';
		else
			dubtab[i][ft_strlen(envp->content)] = '\0';
		dubtab[i][ft_strlen(envp->content) + 1] = '\"';
		dubtab[i][ft_strlen(envp->content) + 2] = '\0';
		i++;
		envp = envp->next;
	}
	dubtab[i] = NULL;
	return (dubtab);
}

char	*ft_export_no_arg(t_list *envp)
{
	char	*ret;
	char	**tri;
	int		i;

	i = 0;
	tri = duptab(envp);
	sort(tri);
	add_quote(tri);
	ret = ft_strdup("");
	while (tri[i])
	{
		ret = ft_strjoin_free(ret, "declare -x ");
		ret = ft_strjoin_free(ret, tri[i++]);
		ret = ft_strjoin_free(ret, "\n");
	}
	ft_free_tab(tri);
	return (ret);
}

void	print_lst(t_list *envp)
{
	while (envp)
	{
		printf("%s\n", (char*)envp->content);
		envp = envp->next;
	}
}

int		modif_var_env(char egual, t_list *envp, char *key, char *value)
{
	int		bool;

	bool = 0;
	while (envp)
	{
		if (!ft_strncmp(envp->content, key, ft_strlen(key))
			&& egual == '=')
		{
			bool = 1;
			free(envp->content);
			envp->content = ft_strjoin_free(key, "=");
			envp->content = ft_strjoin_free(envp->content, value);
			free(value);
			break ;
		}
		envp = envp->next;
	}
	if (bool == 0)
		return (1);
	else
		return (0);
}

char	*ft_export(t_list_cmd *args, t_list *envp)
{
	char	*key;
	char	*value;
	int		i;

	if (!args || !args->str)
		return (ft_export_no_arg(envp));
	while (args)
	{
		i = 0;
		while (args->str[i] && args->str[i] != '=')
			i++;
		key = ft_strndup(args->str, i);
		if (args->str[i] == '=')
			value = ft_strdup(&(args->str[i + 1]));
		else
			value = ft_strdup("");
		if (modif_var_env(args->str[i], envp, key, value))
		{
			ft_lstadd_back(&envp, ft_lstnew(ft_strdup(args->str)));
			free(key);
			free(value);
		}
		args = args->next;
	}
	return (ft_strdup(""));
}
