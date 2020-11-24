/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:38:15 by hthomas           #+#    #+#             */
/*   Updated: 2020/11/24 16:52:19 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes_and_semicolon(t_list_line *lst_line, t_list *env)
{
	t_list_cmd	*cmd;
	char		*ret;
	t_list_line	*start;

	// while (lst_line)
	// {
	// 	if (lst_line->pipe)
	// 	{
	// 		int tmp = lst_line->output;
	// 		lst_line->output = lst_line->next->input;
	// 		lst_line->next->input = tmp;
	// 		ft_printf("output:%d\n", lst_line->output);
	// 		ft_printf("input:%d\n\n", lst_line->next->input);
	// 	}
	// 	lst_line = lst_line->next;
	// }

	start = lst_line;
	while (lst_line)
	{
		if (lst_line->pipe)
		{
			int		fdpipe[2]; // Used to store two ends of first pipe
			pid_t	p;

			if (pipe(fdpipe) == -1) //error
			{
				ft_putstr_fd("pipe: pipe failed\n", STDERR);
				return ;
			}
			// do something ?
			p = fork();
			if (p < 0) //error
			{
				ft_putstr_fd("pipe: fork failed\n", STDERR);
				return ;
			}
			else if (p > 0) //parent process
			{
				close(fdpipe[1]);
				char	*line;
				wait(NULL);
						ft_printf("***Parent\n");
						if (get_next_line(&line, fdpipe[0]) == -1)
							return ;
						ft_printf("***|%s|\n", line);
						free(line);
				close(fdpipe[0]);
			}
			else // child process
			{
				close(fdpipe[0]);
				// lst_line->output = fdpipe[1];
				if (!make_and_exec_cmd(lst_line, env, &ret))
				{
					write(fdpipe[1], ret, strlen(ret) + 1);
					free(ret);
				}
				else
					g_glob.exit = 127;
				close(fdpipe[1]);
				ft_printf("***End child\n");
				exit(0);
			}
			lst_line = lst_line->next; // maybe useless
			break;
		}
		lst_line = lst_line->next;
	}
}