/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/08 15:26:25 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *cmd)
{
	char *ret;
	char *tmp;

	ret = ft_strjoin("minishell: cmd not found: ", cmd);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	free(tmp);
	ft_putstr(ret);
	free(ret);
	exit(0);
}

char	*exec_command(t_cmd *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else if (!ft_strcmp(cmd->str, "echo"))
		return (ft_echo(cmd->next));
	else if (!ft_strcmp(cmd->str, "cd"))
		return (ft_cd(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->str, "export"))
		return (ft_export(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "unset"))
		return (ft_unset(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "env"))
		return (ft_env(cmd->next, envp));
	else if (!ft_strcmp(cmd->str, "exit"))
		return (ft_exit(cmd->next));
	else if (search_command(cmd, envp))
		not_found(cmd->str);
}

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr("\xE2\x9E\xA1 ");
	pwd = getcwd(NULL, 0);
	ft_putstr(pwd);
	free(pwd);
	ft_putstr(": ");
}

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	t_cmd	*lst_cmd;
	char		*ret;

	ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while (1)
	{
		free(input);
		print_prompt();
		get_next_line(&input, 0);
		lst_cmd = NULL;
		if (parse_input(input, &lst_cmd, envp))
			parse_error_exit(input);
		if (lst_cmd)
		{
			if (ret = exec_command(lst_cmd, envp))
			{
				ft_putstr(ret);
				free(ret);
			}
		}
		c_lst_clear(&lst_cmd, c_lst_free_one);
	}
	free(input);
	return (0);
}
