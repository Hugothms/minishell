/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:37:53 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/19 11:52:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		escaped(char *str, int i)
{
	if (i == 0)
		return (0);
	return (str[i - 1] == '\\');
}

int	is_separator(char *str)
{
	return (ft_in_charset(*str, SEPARATORS) || !ft_strncmp(str, ">>", 2));
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
	// free(input);
	// exit(1);
}

char get_separator(char* str)
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
