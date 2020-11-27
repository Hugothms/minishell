/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:38:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/27 10:40:15 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		create_pipe(t_list_line **lst_line, t_list *env)
{
	t_list_cmd	*cmd;
	char		*ret;

	// while ((*lst_line))
	// {
	// 	if ((*lst_line)->pipe)
	// 	{
	// 		int tmp = (*lst_line)->output;
	// 		(*lst_line)->output = (*lst_line)->next->input;
	// 		(*lst_line)->next->input = tmp;
	// 		ft_printf("output:%d\n", (*lst_line)->output);
	// 		ft_printf("input:%d\n\n", (*lst_line)->next->input);
	// 	}
	// 	(*lst_line) = (*lst_line)->next;
	// }

		if ((*lst_line)->pipe)
		{
			int		fdpipe[2]; // Used to store two ends of first pipe
			pid_t	p;

			if (pipe(fdpipe) == -1) //error
			{
				ft_putstr_fd("pipe: pipe failed\n", STDERR);
				return (FAILURE);
			}
			// do something ?
			p = fork();
			if (p < 0) //error
			{
				ft_putstr_fd("pipe: fork failed\n", STDERR);
				return (FAILURE);
			}
			else if (p > 0) //parent process
			{
				close(fdpipe[1]);
				char	*line;
				wait(NULL);
						if (get_next_line(&line, fdpipe[0]) == -1)
							return (FAILURE);
						ft_printf("***|%s|\n", line);
						free(line);
				*lst_line = (*lst_line)->next;
				(*lst_line)->input = fdpipe[0];
				dup2((*lst_line)->input, STDIN);
				// close(fdpipe[0]);
			}
			else // child process
			{
				close(fdpipe[0]);
				// (*lst_line)->output = fdpipe[1];
				if (!make_and_exec_cmd((*lst_line), env, &ret))
				{
					write(fdpipe[1], ret, strlen(ret) + 1);
					free(ret);
				}
				else
					g_glob.exit = 127;
				close(fdpipe[1]);
				exit(0);
			}
			// (*lst_line) = (*lst_line)->next; // maybe useless
			// break;
		}
		return (SUCCESS);
}