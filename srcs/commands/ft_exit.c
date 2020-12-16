/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:34 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/10 16:35:05 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		clear_env_lst(t_list *env)
{
	if (!env)
		return ;
	if (env->next)
		clear_env_lst(env->next);
	free(env->content);
	free(env);
	env = NULL;
}

static void	print_err(int err_code, t_list_cmd *args)
{
	if (err_code == 1 || err_code == 3)
	{
		g_glob.exit = 2;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args->str, STDERR);
		ft_putstr_fd(": nurmeric argument needed\n", STDERR);
	}
	if (err_code == 2)
	{
		g_glob.exit = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
	}
}

static int	check_args(t_list_cmd *args)
{
	int ret;
	int i;

	i = 0;
	ret = 0;
	if (!args)
		return (0);
	if (args->str[0] == '-')
		i++;
	while (args->str[i])
	{
		if (!ft_isdigit(args->str[i]))
			ret = 1;
		i++;
	}
	if (c_lst_size(args) > 1)
		ret += 2;
	print_err(ret, args);
	if (ret == 2)
		ret = -1;
	return (ret);
}

char		*ft_exit(t_list_line *lst_line, t_list *env)
{
	int		err;

	err = check_args(lst_line->cmd->next);
	if (err >= 0)
	{
		clear_env_lst(env);
		free(g_glob.path);
		if (!err)
			if (lst_line->cmd->next &&
					(err = ft_atoi_strict(lst_line->cmd->next->str)))
				g_glob.exit = err;
		l_lst_clear(lst_line);
		exit(g_glob.exit);
	}
	return (NULL);
}
