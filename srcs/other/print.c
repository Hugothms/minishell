/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:23:14 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 14:19:25 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr_fd("\033[1;32m➜ \033[1;36m", STDERR);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_putstr_fd(g_glob.path, STDERR);
	else
		ft_putstr_fd(pwd, STDERR);
	free(pwd);
	ft_putstr_fd("\033[0m$ ", STDERR);
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

int		print_synt_err(void)
{
	g_glob.exit = 2;
	ft_putstr_fd("minishell: syntax error\n", STDERR);
	return (-1);
}

void	parse_error(char *input, t_list_line *lst_line)
{
	print_synt_err();
	print_prompt();
	l_lst_clear(lst_line);
	free(input);
}
