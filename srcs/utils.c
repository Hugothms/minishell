/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/21 18:24:23 by hthomas          ###   ########.fr       */
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

void	add_substr_to_cmd(char *input, t_list_cmd **cmd, int size, int flags)
{
	char *str;

	if (size <= 0)
		return ;
	while (!(flags & F_SIMPLE_QUOTES) && !(flags & F_DOUBLE_QUOTES) && ft_in_charset(*input, WHITESPACES))
		input++;
	str = ft_strndup(input, size);
	c_lst_add_back(cmd, c_lst_new(str, flags));
	free(str); //! todo
}

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\' && !escaped(str, i - 1));
}

int		is_separator(char *str, int i)
{
	return (ft_in_charset(str[i], SEPARATORS) || !ft_strncmp(&str[i], ">>", 2));
}

int		in_quotes(t_list_cmd *cmd)
{
	return ((cmd->flags & F_SIMPLE_QUOTES) || \
	(cmd->flags & F_DOUBLE_QUOTES));
}

void	parse_error(char *input, t_list_line *lst_line)
{
	ft_putstr_fd("minishell: syntax error\n", STDERR);
	l_lst_clear(lst_line);
	free(input);
	// exit(1);
}

char	get_separator(char *str)
{
	char	separator;

	separator = str[0];
	if (str[1])
		separator = '='; // if separator is ">>" we save char '='
	return (separator);
}

void	cmd_plusplus_free(t_list_cmd **cmd)
{
	t_list_cmd	*tmp;

	tmp = *cmd;
	*cmd = (*cmd)->next;
	c_lst_del_one(tmp);
}

char	**lst_to_strs(t_list_cmd *cmd)
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
