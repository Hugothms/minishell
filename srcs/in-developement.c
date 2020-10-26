/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in-developement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 10:19:03 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/26 10:19:06 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
