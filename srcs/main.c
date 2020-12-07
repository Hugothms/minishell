/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 14:49:48 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	increment_shlvl(t_list *env)
{
	t_list_cmd	*args;
	char		*tmp;
	int			sh_lvl;

	args = c_lst_new("$SHLVL", F_VAR_ENV);
	replace_all_var_env(args, env);
	sh_lvl = ft_atoi(args->str);
	c_lst_clear(args);
	args = c_lst_new("SHLVL", F_NOTHING);
	tmp = ft_itoa(sh_lvl + 1);
	args->str = ft_strjoin_free(args->str, "=");
	args->str = ft_strjoin_free(args->str, tmp);
	free(tmp);
	tmp = ft_export(args, env);
	free(tmp);
	c_lst_clear(args);
}

void	sighandler(int signum)
{
	if (g_glob.pid && signum == SIGINT)
	{
		kill(g_glob.pid, signum);
		ft_putstr_fd("\n", STDERR);
		g_glob.exit = 130;
		g_glob.pid = 0;
	}
	else if (g_glob.pid && signum == SIGQUIT)
	{
		kill(g_glob.pid, signum);
		ft_putstr_fd("Quit (core dumped)\n", STDERR);
		g_glob.exit = 131;
		g_glob.pid = 0;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		print_prompt();
	}
}

void	init_main(t_list **env, char **envp)
{
	g_glob.exit = 0;
	g_glob.path = getcwd(NULL, 0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	set_env(envp, env);
	ft_putstr_fd(WELCOME_MSG, STDERR);
	increment_shlvl(*env);
	print_prompt();
}

void	free_main(t_list *env, char *input)
{
	free(g_glob.path);
	clear_env_lst(env);
	free(input);
	ft_putstr_fd("\n", STDERR);
}

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	t_list_line	*lst_line;
	t_list		*env;

	if (argc != 1)
	{
		ft_putstr_fd("ERROR: Too many argument\n", STDERR);
		return (FAILURE);
	}
	init_main(&env, envp);
	while (get_next_line(&input, 0) > 0)
	{
		lst_line = NULL;
		if (parse_input(input, &lst_line, env))
		{
			parse_error(input, lst_line);
			continue;
		}
		free(input);
		exec_line(lst_line, env);
		print_prompt();
	}
	free_main(env, input);
	return (g_glob.exit);
}
