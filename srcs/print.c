/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:23:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/23 18:12:57 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr_fd("\xE2\x9E\xA1 ", STDOUT);
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, STDOUT);
	free(pwd);
	ft_putstr_fd("$ ", STDOUT);
}

void	not_found(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	ret = ft_strjoin_free(ret, ": command not found\n");
	g_glob.exit = CMD_NOT_FOUND;
	ft_putstr_fd(ret, STDERR);
	free(ret);
	exit(CMD_NOT_FOUND);
}

void	parse_error(char *input, t_list_line *lst_line)
{
	g_glob.exit = 1;
	ft_putstr_fd("minishell: syntax error\n", STDERR);
	l_lst_clear(lst_line);
	free(input);
	// exit(SYNTAX_ERROR);
}
