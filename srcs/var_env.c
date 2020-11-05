/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:52 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/05 17:53:55 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_var_env2(t_list_cmd *cmd, t_list *env, int i)
{
	int		size;
	int		pos_sep;
	char	*key;
	char	*var;

	while (env)
	{
		var = (char *)env->content;
		pos_sep = 0;
		while (cmd->str[pos_sep] && !ft_in_charset(cmd->str[pos_sep], "= \t"))
			pos_sep++;
		size = ft_strlen(&(cmd->str[i]));
		if (pos_sep && pos_sep < size)
			size = pos_sep;
		if (!ft_strncmp(env->content, &(cmd->str[i + 1]), size - 1) && var[size - 1] == '=')
		{
			key = ft_strdup(&cmd->str[pos_sep]);
			// ft_printf("((((((((((((%s)))))))))%d)))%s\n", &cmd->str[i], pos_sep, key);
			cmd->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/¯
			cmd->str = ft_strjoin_free(cmd->str, &var[size]);
			if (pos_sep)
				cmd->str = ft_strjoin_free(cmd->str, key);
			free(key);
			return ;
		}
		env = env->next;
	}
	cmd->str[i] = '\0';
}

int		replace_var_env(t_list_cmd *cmd, t_list *env)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			if (cmd->str[i] == '$' && !escaped(cmd->str, i) && !(cmd->flags & F_SIMPLE_QUOTE) && cmd->str[i + 1] > 32)
				replace_var_env2(cmd, env, i);
			i++;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	replace_all_var_env(t_list_cmd *cmd, t_list *env)
{
	while (cmd)
	{
		if (cmd->flags & F_VAR_ENV)
			replace_var_env(cmd, env);
		cmd = cmd->next;
	}	
}