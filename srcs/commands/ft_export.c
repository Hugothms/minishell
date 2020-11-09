/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:36 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/06 17:52:13 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**duptab(t_list *env)
{
	char	**dubtab;
	int		i;

	i = ft_lstsize(env);
	dubtab = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		dubtab[i] = malloc(sizeof(char) * (ft_strlen(env->content) + 3));
		ft_strcpy(dubtab[i], env->content);
		if (have_egual(env->content))
			dubtab[i][ft_strlen(env->content)] = '#';
		else
			dubtab[i][ft_strlen(env->content)] = '\0';
		dubtab[i][ft_strlen(env->content) + 1] = '\"';
		dubtab[i][ft_strlen(env->content) + 2] = '\0';
		i++;
		env = env->next;
	}
	dubtab[i] = NULL;
	return (dubtab);
}

char	*ft_export_no_arg(t_list *env)
{
	char	*ret;
	char	**tri;
	int		i;

	i = 0;
	tri = duptab(env);
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

void	print_lst(t_list *env)
{
	while (env)
	{
		printf("%s\n", (char*)env->content);
		env = env->next;
	}
}

int		modif_var_exp(char egual, t_list *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->content, key, ft_strlen(key)))
		{
			if (egual == '=')
			{
				free(env->content);
				env->content = ft_strjoin_free(key, "=");
				env->content = ft_strjoin_free(env->content, value);
			}
			else
				free(key);
			free(value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

char	*ft_export(t_list_cmd *args, t_list *env)
{
	char	*key;
	char	*value;
	int		i;

	if (!args || !args->str)
		return (ft_export_no_arg(env));
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
		if (modif_var_exp(args->str[i], env, key, value))
		{
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(args->str)));
			free(key);
			free(value);
		}
		args = args->next;
	}
	return (ft_strdup(""));
}
