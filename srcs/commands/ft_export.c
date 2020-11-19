/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:36 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/19 15:08:42 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_lst(t_list *env)
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
	tri = dup_lst(env);
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

int		check_identifier(char *key)
{
	int		i;

	i = 0;
	if (key[i] != '\0')
	{
		while (key[i])
		{
			if (!ft_isalpha(key[i]))
				return (0);
			i++;
		}
		if (key[i] == '\0')
			return (1);
	}
	else
		return (0);
}

int		set_keyval(t_list_cmd *args, char **key, char **value)
{
	int		i;

	i = 0;
	while (args->str[i] && args->str[i] != '=')
		i++;
	*key = ft_strndup(args->str, i);
	if (args->str[i] == '=')
		*value = ft_strdup(&(args->str[i + 1]));
	else
		*value = ft_strdup("");
	if (check_identifier(*key))
		return (1);
	else
	{
		g_glob.exit = 1;
		if (*key[0] == '\0' && *value[0])
			ft_printf("minishell: export: « %s=%s » : not valid identifier\n",
						*key, *value);
		else
			ft_printf("minishell: export: « %s » : not valid identifier\n",
						*key);
		free(*key);
		free(*value);
		return (0);
	}
}

char	*ft_export(t_list_cmd *args, t_list *env)
{
	char	*key;
	char	*value;

	g_glob.exit = 0;
	if (!args || !args->str || (args->str[0] != '=' && args->flags == 256))
		return (ft_export_no_arg(env));
	while (args)
	{
		if (set_keyval(args, &key, &value))
			if (modif_var_exp(args->str[ft_strlen(key)], env, key, value))
			{
				ft_lstadd_back(&env, ft_lstnew(ft_strdup(args->str)));
				free(key);
				free(value);
			}
		args = args->next;
	}
	return (ft_strdup(""));
}
