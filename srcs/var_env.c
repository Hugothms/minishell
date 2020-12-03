/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:46:52 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/03 15:15:26 by vmoreau          ###   ########.fr       */
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

void	remove_double_char(char *str, char *charset)
{
	int	i;

	i = 0;
	if (!str[i] || !str[i + 1])
		return ;
	while (str[i])
	{
		// ft_printf("%d:%c,%c\n", i , str[i], str[ i + 1]);
		if (ft_in_charset(str[i], charset) && ft_in_charset(str[i + 1], charset))
		{
			// ft_printf("ok\n");
			ft_strcpy(&str[i], &str[i + 1]);
			// ft_printf("%s\n", str);
			continue;
		}
		i++;
	}
}

static char	*format_var_env(t_list *env, int size, int space_begin, int flags)
{
	char	*ret;
	char	*tmp;
	int		i;

	if (!ft_strlen(&((char *)env->content)[size]))
		return (ft_strdup(""));
	if (flags & F_DOUBLE_QUOTE)
		ret = ft_strdup(&((char *)env->content)[size]);
	else
		ret = ft_strtrim(&((char *)env->content)[size], WSP);
	if (space_begin && ft_in_charset(((char *)env->content)[size], WSP))
	{
		tmp = ft_strjoin(" ", ret);
		free(ret);
		ret = tmp;
	}
	// ft_putstr("|");
	// ft_putstr(ret);
	// ft_putstr("|\n");
	if (!(flags & F_DOUBLE_QUOTE))
		remove_double_char(ret, WSP);
	return (ret);
}

static void	replace_var_env(t_list_cmd *cmd, t_list *env, int *i, int size)
{
	char	*after;
	char	*tmp;

	after = ft_strdup(&cmd->str[*i + size]);
	cmd->str[*i] = '\0';
	tmp = format_var_env(env, size, *i, cmd->flags);
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

	if (ft_isdigit(cmd->str[*i + 1]))
	{
		ft_strcpy(&cmd->str[*i], &cmd->str[*i + 2]);
		return ;
	}
	while (env)
	{
		size = 1;
		// while (cmd->str[*i + size] && !ft_in_charset(cmd->str[*i + size], "\\\"`$"))
		while (ft_isalnum(cmd->str[*i + size]) || cmd->str[*i + size] == '_')
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
			if (cmd->str[i] == '$' && cmd->str[i + 1] != '\\' && cmd->str[i + 1] != '%' && !escaped(cmd->str, i) &&\
			!(cmd->flags & F_SIMPLE_QUOTE) && (cmd->str[i + 1] > '$' ||\
			(!cmd->str[i + 1] && cmd->flags & F_NO_SP_AFTER)))
			{
				if (cmd->str[i + 1] == '?')
					err_code(cmd, env, i);
				else if (cmd->str[i + 1] != '/')
				{
					test_var_env(cmd, env, &i);
					continue ;
				}
			}
			i++;
		}
		cmd = cmd->next;
	}
}
