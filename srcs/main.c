/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/25 11:06:14 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_env(t_list **env)
{
	char	*keyval;
	char	*pwd;

	keyval = ft_strdup("SHLVL=0");
	ft_lstadd_back(env, ft_lstnew(keyval));
	pwd = getcwd(NULL, 0);
	keyval = ft_strjoin("PWD=", pwd);
	free(pwd);
	ft_lstadd_back(env, ft_lstnew(keyval));
	keyval = ft_strdup("OLDPWD=");
	ft_lstadd_back(env, ft_lstnew(keyval));
}

void	set_env(char **envp, t_list **env)
{
	int		i;
	char	*keyval;

	i = 0;
	*env = NULL;
	if (envp[i])
	{
		while (envp[i])
		{
			keyval = ft_strdup(envp[i]);
			ft_lstadd_back(env, ft_lstnew(keyval));
			i++;
		}
	}
	else
		fill_env(env);
}

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
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT);
		print_prompt();
		g_glob.exit = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT);
		print_prompt();
		g_glob.exit = 131;
	}
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
	g_glob.exit = 0;
	g_glob.path = getcwd(NULL, 0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	set_env(envp, &env);
	ft_putstr(WELCOME_MSG);
	increment_shlvl(env);
	print_prompt();
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
	free(g_glob.path);
	clear_env_lst(env);
	free(input);
	ft_printf("\n");
	return (g_glob.exit);
}
