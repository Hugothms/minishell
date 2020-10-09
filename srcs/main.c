/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 11:22:41 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *cmd)
{
	char *ret;
	char *tmp;

	ret = ft_strjoin("minishell: command not found: ", cmd);
	tmp = ret;
	ret = ft_strjoin(ret, "\n");
	free(tmp);
	ft_putstr(ret);
	free(ret);
	exit(0);
}

char	*exec_command(t_list *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "echo"))
		return (ft_echo(cmd->next));
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "cd"))
		return (ft_cd(cmd->next, envp));
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "export"))
		return (ft_export(cmd->next, envp));
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "unset"))
		return (ft_unset(cmd->next, envp));
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "env"))
		return (ft_env(cmd->next, envp));
	else if (!ft_strcmp(((t_word*)cmd->content)->str, "exit"))
		return (ft_exit(cmd->next));
	else if (search_command(cmd, envp))
		not_found(((t_word*)cmd->content)->str);
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
	t_list		*lst_cmd;
	t_list		*cmd;
	char		*ret;

	lst_cmd = NULL;
	ft_putstr(WELCOME_MSG);
	input = malloc(1);
	while (1)
	{
		free(input);
		print_prompt();
		get_next_line(&input, 0);
		if (parse_input(input, lst_cmd, envp))
			parse_error_exit(input);
		while (((t_list_cmd*)lst_cmd->content)->cmd)
		{
			if (((t_list_cmd*)lst_cmd->content)->cmd)
			{
				if (ret = exec_command(((t_list_cmd*)lst_cmd->content)->cmd, envp))
				{
					ft_putstr(ret);
					free(ret);
				}
			}
			ft_lstclear(&((t_list_cmd*)lst_cmd->content)->cmd, free_cmd);
			lst_cmd = lst_cmd->next;
		}
	}
	free(input);
	return (0);
}
