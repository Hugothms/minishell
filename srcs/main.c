/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/06 20:31:10 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *command)
{
	char *ret;
	char *tmp;

	ret = ft_strjoin("minishell: command not found: ", command);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	free(tmp);
	ft_putstr(ret);
	free(ret);
	exit(0);
}

char	*exec_command(t_list_command *command, char **envp)
{
	if (!command)
		return (NULL);
	else if (!ft_strcmp(command->str, "echo"))
		return (ft_echo(command->next));
	else if (!ft_strcmp(command->str, "cd"))
		return (ft_cd(command->next, envp));
	else if (!ft_strcmp(command->str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(command->str, "export"))
		return (ft_export(command->next, envp));
	else if (!ft_strcmp(command->str, "unset"))
		return (ft_unset(command->next, envp));
	else if (!ft_strcmp(command->str, "env"))
		return (ft_env(command->next, envp));
	else if (!ft_strcmp(command->str, "exit"))
		return (ft_exit(command->next));
	else if (search_command(command, envp))
		not_found(command->str);
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
	char			*input;
	t_list_command	*command;
	char			*ret;

	ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while (1)
	{
		free(input);
		print_prompt();
		get_next_line(&input, 0);
		command = NULL;
		if (parse_input(input, &command, envp))
		{
			ft_putstr("minishell: parse error\n");
			free(input);
			exit(1);
		}
		if (command)
		{
			if (ret = exec_command(command, envp))
			{
				ft_putstr(ret);
				free(ret);
			}
		}
		c_lstclear(&command, c_free);
	}
	free(input);
	return (0);
}
