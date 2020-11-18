/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:52 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/18 16:49:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		err_code(t_list_cmd *cmd, t_list *env, int i)
{
	int		size;
	int		pos_sep;
	char	*after;
	char	*var;

	size = ft_strlen(&(cmd->str[i]));
	if (2 < size)
		size = 2;
	after = ft_strdup(&cmd->str[2]);
	cmd->str[i] = '\0';
	var = ft_itoa(g_glob.exit);
	cmd->str = ft_strjoin_free(cmd->str, var);
	free(var);
	cmd->str = ft_strjoin_free(cmd->str, after);
	free(after);
}

static char	*format_var_env(t_list *env, int size)
{
	char	*ret;
	char	*tmp;
	int		i;

	ret = ft_strtrim(&((char *)env->content)[size], WSP);
	if (ft_in_charset(((char *)env->content)[size], WSP))
	{
		tmp = ft_strjoin(" ", ret);
		free(ret);
		ret = tmp;
	}
	i = 1;
	while (ret[i])
	{
		if (ft_in_charset(ret[i], WSP) && ft_in_charset(ret[i - 1], WSP))
			ft_strcpy(&ret[i - 1], &ret[i--]);
		i++;
	}
	ft_printf("str:%s\n", ret);
	return (ret);
}

static void	replace_var_env(t_list_cmd *cmd, t_list *env, int *i, int size)
{
	char	*after;
	char	*tmp;

	after = ft_strdup(&cmd->str[*i + size]);
	cmd->str[*i] = '\0';
	tmp = format_var_env(env ,size);
	cmd->str = ft_strjoin_free(cmd->str, tmp);
	free(tmp);
	size = ft_strlen(cmd->str);
	cmd->str = ft_strjoin_free(cmd->str, after);
	*i = size - 1;
	free(after);
}

void		test_var_env(t_list_cmd *cmd, t_list *env, int *i)
{
	int		size;

	while (env)
	{
		size = 1;
		while (ft_isalnum(cmd->str[*i + size]))
			size++;
		if (!ft_strncmp(env->content, &(cmd->str[*i + 1]), size - 1) &&\
		((char *)env->content)[size - 1] == '=')
			return (replace_var_env(cmd, env, i, size));
		env = env->next;
	}
	ft_strcpy(&cmd->str[*i], &cmd->str[*i + size]);
}

void		replace_all_var_env(t_list_cmd *cmd, t_list *env)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			if (cmd->str[i] == '$' && !escaped(cmd->str, i) &&\
			!(cmd->flags & F_SIMPLE_QUOTE) && cmd->str[i + 1] > 32)
			{
				if (cmd->str[i + 1] == '?')
					err_code(cmd, env, i);
				else
					test_var_env(cmd, env, &i);
			}
			i++;
		}
		cmd = cmd->next;
	}
}
