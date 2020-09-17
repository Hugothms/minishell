/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:52:58 by hthomas           #+#    #+#             */
/*   Updated: 2020/09/17 17:14:59 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(void)
{
	return(getcwd(NULL, 0));
}

char	*ft_echo(char **args)
{
	int		i;
	char	*ret;

	i = 0;
	if (ft_strcmp(args[i], "-n"))
		i++;
	// if (echo_args_valid())
	{
		while(args[i])
		{
			ft_strjoin(ret, args[i]);
			if (args[i + 1])
				ft_strjoin(args[i], " ");
			i++;
		}
	}
	return (ret);
}

char	*ft_cd(char **args)
{
	return(NULL);
}

char	*ft_env(char **args)
{
	return(NULL);
}

char	*ft_exit(char **args)
{
	return(NULL);
}

char	*ft_export(char **args)
{
	return(NULL);
}

char	*ft_unset(char **args)
{
	return(NULL);
}


// echo	with option ’-n’
// cd		with only a relative or absolute path
// pwd		without any options
// export	without any options
// unset	without any options
// env		without any options and any arguments
// exit	without any options
