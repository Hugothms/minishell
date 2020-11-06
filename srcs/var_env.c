/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:52 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/06 21:09:25 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	err_code(t_list_cmd *cmd, t_list *env, int i, int *exit_status)
{
	int		size;
	int		pos_sep;
	char	*after;
	char	*var;

	size = ft_strlen(&(cmd->str[i]));
	if (2 < size)
		size = 2;
	after = ft_strdup(&cmd->str[2]);
	cmd->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/¯
	var = ft_itoa(*exit_status);
	cmd->str = ft_strjoin_free(cmd->str, var);
	free(var);
	cmd->str = ft_strjoin_free(cmd->str, after);
	free(after);
	return ;
	cmd->str[i] = '\0';
}

void	replace_var_env2(t_list_cmd *cmd, t_list *env, int i, int *exit_status)
{
	int		size;
	int		pos_sep;
	char	*after;

	while (env)
	{
		pos_sep = 1;
		while (cmd->str[pos_sep] && !ft_in_charset(cmd->str[pos_sep], AFTER_VAR_ENV))
			pos_sep++;
		size = ft_strlen(&(cmd->str[i]));
		if (pos_sep && pos_sep < size)
			size = pos_sep;
		if (!ft_strncmp(env->content, &(cmd->str[i + 1]), size - 1) && ((char *)env->content)[size - 1] == '=')
		{
			after = ft_strdup(&cmd->str[pos_sep]);
			cmd->str[i] = '\0';// wil maybe cause some leaks later ¯\_(ツ)_/¯
			cmd->str = ft_strjoin_free(cmd->str, &((char *)env->content)[size]);
			if (pos_sep)
				cmd->str = ft_strjoin_free(cmd->str, after);
			free(after);
			return ;
		}
		env = env->next;
	}
	cmd->str[i] = '\0';
}

int		replace_var_env(t_list_cmd *cmd, t_list *env, int *exit_status)
{
	int	i;

	while (cmd)
	{
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			if (cmd->str[i] == '$' && !escaped(cmd->str, i) && !(cmd->flags & F_SIMPLE_QUOTE) && cmd->str[i + 1] > 32)
			{
				if (cmd->str[i + 1] == '?')
					err_code(cmd, env, i, exit_status);
				else
					replace_var_env2(cmd, env, i, exit_status);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	replace_all_var_env(t_list_cmd *cmd, t_list *env, int *exit_status)
{
	while (cmd)
	{
		if (cmd->flags & F_VAR_ENV)
			replace_var_env(cmd, env, exit_status);
		cmd = cmd->next;
	}	
}