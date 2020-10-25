/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:21:43 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/25 14:15:03 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: command not found: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd("\n", STDERR);
	exit(0);
}

char	*exec_cmd(t_list_cmd *cmd, char **envp)
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
		return (ft_env(envp));
	else if (!ft_strcmp(cmd->str, "exit"))
		return (ft_exit(cmd->next));
	else if (search_command(cmd, envp))
		not_found(cmd->str);
	return (NULL);
}

void	print_prompt(void)
{
	char	*pwd;

	ft_putstr_fd("\xE2\x9E\xA1 ", STDOUT);
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, STDOUT);
	free(pwd);
	ft_putstr_fd("$ ", STDOUT);
}

void	create_pipes_and_semicolon(t_list_line *lst_line)
{


}

void	open_fd(t_list_line *lst_line, t_list_cmd *cmd)
{
	char *filename = cmd->next->str;
	// ft_printf("filename:%s\n", filename);			
	// ft_printf("before:%d\n", start->output);
	if (!filename)
		ft_putstr_fd("pas de filename\n", STDERR); //! todo
	if (cmd->flags & F_INPUT)
	{
		// input = filename; //! todo
		dup2(lst_line->input, STDIN);
	}
	else if (cmd->flags & F_APPEND)
		lst_line->output = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->flags & F_OUTPUT)
		lst_line->output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->flags & F_OUTPUT)
		dup2(lst_line->output, STDOUT);

	// ft_printf("open:%d\n", start->output);
	if (lst_line->output < 0)
		ft_putstr_fd("error open\n", STDERR);
}

void	redirections(t_list_line *lst_line, char **envp)
{
	int	fd_outold;
	int	fd_inold;
	fd_outold = dup(STDOUT);
	fd_inold = dup(STDIN);

	// int fd_outold = STDOUT;
	// int fd_inold = STDIN;
	lst_line->output = STDOUT;
	// ft_printf("lst_line->cmd->str:%s\n", lst_line->cmd->str);
	// ft_printf("lst_line->cmd->flags:%i\n", lst_line->cmd->flags);
	
	t_list_cmd *cmd = lst_line->cmd;
	while (cmd)
	{
		while (cmd->flags & (F_OUTPUT + F_INPUT))
		{
			open_fd(lst_line, cmd);
			c_lst_remove_next_one(cmd);
			t_list_cmd *tmp = cmd;
			lst_line->cmd = cmd->next;
			cmd = lst_line->cmd;
			c_lst_free_one(tmp);
		}
		if (cmd->next && cmd->next->flags & (F_OUTPUT + F_INPUT))
		{
			open_fd(lst_line, cmd->next);
			c_lst_remove_next_one(cmd->next);
			t_list_cmd *tmp = cmd->next;
			cmd->next = cmd->next->next;
			c_lst_free_one(tmp);
		}
		cmd = cmd->next;
	}
	
		char *ret;
		if ((ret = exec_cmd(lst_line->cmd, envp)))
		{
			// ft_printf("output:%d\n", lst_line->output);
			ft_putstr_fd(ret, lst_line->output);
			free(ret);
		}
		if (lst_line->output > 2 && close(lst_line->output) < 0)
			ft_putstr_fd("error close\n", STDERR);
		dup2(fd_outold, STDOUT);
		dup2(fd_inold, STDIN);
}

void	exec_line(t_list_line *lst_line, char **envp)
{
	char		*ret;
	t_list_line	*start;

	start = lst_line;
	int i = 0;
	// ft_printf("text\n");
	while (lst_line)
	{
		redirections(lst_line, envp);

		// ft_printf("\nexec_line number:%d\n",i);
		// char **tab = lst_to_strs(lst_line->cmd);
		// ft_printf("***********************************\n", 0);
		// ft_print_tabstr(tab);
		// ft_printf("***********flags:%d\n", lst_line->cmd->flags);
		// ft_free_tab(tab);

		// tab = lst_to_strs(lst_line->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->next->cmd->flags);
		// ft_free_tab(tab);

		// tab = lst_to_strs(lst_line->next->next->cmd);
		// ft_printf("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->next->next->cmd->flags);
		// ft_free_tab(tab);

		// ft_printf("***********************************\n");
		
		//! ici exec + dup2

		lst_line = lst_line->next;
		i++;
	}
	l_lst_clear(start);
}

void	in_developement_by_hugo(t_list_line *lst_line, char **envp)
{
	char		*ret;
	t_list_line	*start;

	start = lst_line;

	while (lst_line)
	{
		int	fd_out;
		int	fd_outold;
		int	fd_in;
		int	fd_inold;
		fd_out = STDOUT;
		fd_outold = STDOUT;
		fd_in = STDIN;
		fd_inold = STDIN;
		if (lst_line->cmd->flags)
		{
			char *filename = lst_line->next->cmd->next->str;
			if (!filename)
				ft_putstr_fd("pas de filename\n", STDERR);
			if (lst_line->cmd->flags & F_INPUT)
			{
				fd_in = open(filename, O_RDONLY);
				fd_inold = dup(STDIN);
				dup2(fd_in, STDIN);
			}
			else if (lst_line->cmd->flags & F_OUTPUT || lst_line->cmd->flags & F_APPEND)
			{
				if (lst_line->cmd->flags & F_OUTPUT)
					fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (lst_line->cmd->flags & F_OUTPUT)
					fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				fd_outold = dup(STDOUT);
				dup2(fd_out, STDOUT);
			}
			else if (lst_line->cmd->flags & F_PIPE)
			{
				int		tab[2];	// Used to store two ends of first pipe
				pid_t	p;

				if (pipe(tab) == -1)	//error
				{
					ft_putstr_fd("pipe failed\n", STDERR);
					return ;
				}
				// do something ?
				p = fork();
				if (p < 0)		//error
				{
					ft_putstr_fd("fork failed\n", STDERR);
					return ;
				}



    // else if (p > 0)
    // {
    //     char concat_str[100];

    //     close(tab[0]);  // Close reading end of first pipe

    //     // Write input string and close writing end of first pipe.
    //     write(tab[1], input_str, strlen(input_str)+1);
    //     close(tab[1]);

    //     // Wait for child to send a string
    //     wait(NULL);
    //     printf("Concatenated string %s\n", concat_str);
    // }

    // // child process
    // else
    // {
    //     close(tab[1]);  // Close writing end of first pipe

    //     // Read a string using first pipe
    //     char concat_str[100];
    //     read(tab[0], concat_str, 100);

    //     // Concatenate a fixed string with it
    //     int k = strlen(concat_str);
    //     int i;
    //     for (i=0; i<strlen(fixed_str); i++)
    //         concat_str[k++] = fixed_str[i];

    //     concat_str[k] = '\0';   // string ends with '\0'

    //     // Close both reading ends
    //     close(tab[0]);
    //     exit(0);
    // }



				else if (p > 0)	// Parent process
				{
					if ((ret = exec_cmd(lst_line->cmd, envp)))
					{
						ft_putstr_fd(ret, STDOUT);
						free(ret);
					}
				}
				else			// Child process
				{
					wait(NULL);
					if ((ret = exec_cmd(lst_line->next->cmd, envp)))
					{
						ft_putstr_fd(ret, STDOUT);
						free(ret);
					}
				}
				fd_inold = dup(STDIN);
				dup2(STDOUT, STDIN);

				lst_line = lst_line->next;
				break ;
			}
			if (fd_out < 0 )
				ft_putstr_fd("error open out\n", STDERR);
			if (fd_in < 0)
				ft_putstr_fd("error open in\n", STDERR);
			t_list_cmd *tmp = lst_line->next->cmd->next;
			lst_line->next->cmd = tmp;
			c_lst_free_one(tmp);
		}
		///////////////////////////////////////////////////////////////////////////
		if ((ret = exec_cmd(lst_line->cmd, envp)))
		{
			ft_putstr_fd(ret, STDOUT);
			free(ret);
		}
		///////////////////////////////////////////////////////////////////////////
		if (fd_out > 2 && close(fd_out) < 0)
			ft_putstr_fd("error close out\n", STDERR);
		if (fd_in > 2 && close(fd_in) < 0)
			ft_putstr_fd("error close in\n", STDERR);
		dup2(fd_outold, STDOUT);
		dup2(fd_inold, STDIN);
		lst_line = lst_line->next;
	}
	l_lst_clear(start);
}

int		main(const int argc, char *argv[], char *envp[])
{
	char		*input;
	t_list_line	*lst_line;

	ft_putstr(WELCOME_MSG);
	while (1)
	{
		print_prompt();
		get_next_line(&input, 0);
		lst_line = NULL;
		if (parse_input(input, &lst_line, envp))
		{
			parse_error(input, lst_line);
			continue ;
		}

		// char **tab = lst_to_strs(lst_line->cmd);
		// ft_putstr("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->cmd->flags);
		// ft_free_tab(tab);

		// tab = lst_to_strs(lst_line->next->cmd);
		// ft_putstr("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->cmd->next->flags);
		// ft_free_tab(tab);

		// tab = lst_to_strs(lst_line->next->next->cmd);
		// ft_putstr("***********************************\n");
		// ft_print_tabstr(tab);
		// ft_printf("**************************%d\n", lst_line->cmd->next->next->flags);
		// ft_free_tab(tab);

		// ft_putstr("***********************************\n");

		create_pipes_and_semicolon(lst_line);
		exec_line(lst_line, envp);
		free(input);
	}
	return (0);
}
