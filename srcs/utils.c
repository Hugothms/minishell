/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/20 12:03:58 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_par(t_parse *par)
{
	par->in_simple = 0;
	par->in_double = 0;
	par->i = 0;
	par->pos = 0;
}

/*
** Add substring to command (in queue)
** @param input	The string where to extract the substring
** @param cmd	The adress of an element of command
** @param size	The size of the string to add to command
** @param flags	The flags to add to the command
*/

void	add_cmd(char *input, t_list_cmd **cmd, int size, int flags)
{
	char *str;

	if (size < 0)
		return ;
	else if (size == 0)
		str = ft_strdup("");
	else
	{
		while (!(flags & F_SIMPLE_QUOTE) && !(flags & F_DOUBLE_QUOTE)\
		&& ft_in_charset(*input, WSP))
			input++;
		str = ft_strndup(input, size);
	}
	c_lst_add_back(cmd, c_lst_new(str, flags));
	free(str);
}

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\' && !escaped(str, i - 1));
}

int		is_separator(char *str, int i)
{
	return (ft_in_charset(str[i], SYMBOLS) || !ft_strncmp(&str[i], ">>", 2));
}

int		in_quotes(t_list_cmd *cmd)
{
	return ((cmd->flags & F_SIMPLE_QUOTE) || \
	(cmd->flags & F_DOUBLE_QUOTE));
}

void	parse_error(char *input, t_list_line *lst_line)
{
	g_glob.exit = 1;
	ft_putstr_fd("minishell: syntax error\n", STDERR);
	l_lst_clear(lst_line);
	free(input);
	// exit(SYNTAX_ERROR);
}

int		get_flags(char *str)
{
	int		flags;

	flags = 0;
	if (*str == ';')
		flags += F_SEMICOLON;
	else if (*str == '|')
		flags += F_PIPE;
	else if (*str == '<')
		flags += F_INPUT;
	else if (*str == '>')
	{
		flags += F_OUTPUT;
		if (str[1] == '>')
			flags += F_APPEND;
	}
	return (flags);
}

void	cmd_plusplus_free(t_list_cmd **cmd)
{
	t_list_cmd	*tmp;

	tmp = *cmd;
	*cmd = (*cmd)->next;
	c_lst_free_one(tmp);
}

char	**cmd_to_strs(t_list_cmd *cmd)
{
	char	**argv;
	int		i;

	if (!(argv = malloc(sizeof(*argv) * (c_lst_size(cmd) + 1))))
		return (NULL);
	i = 0;
	while (cmd)
	{
		argv[i++] = ft_strdup(cmd->str);
		cmd = cmd->next;
	}
	argv[i] = NULL;
	return (argv);
}

char	**lst_to_chartab(t_list *env)
{
	char	**ret;
	int		i;

	if (!(ret = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1))))
		return (NULL);
	i = 0;
	while (env)
	{
		ret[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	modif_var_env(t_list *env, char *key, char *new_value)
{
	while (env)
	{
		if (!ft_strncmp(env->content, key, ft_strlen(key)))
		{
			free(env->content);
			env->content = ft_strjoin(key, "=");
			env->content = ft_strjoin_free(env->content, new_value);
		}
		env = env->next;
	}
}
