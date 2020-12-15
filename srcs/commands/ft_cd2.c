/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 22:17:31 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/15 22:17:37 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char	*ft_cd2(t_list_cmd *args, t_list *env, struct stat *stats)
{
	if (chdir(&find_var_env(env, "HOME=")[5]))
	{
		if (find_var_env(env, "HOME=") == NULL)
			return (error_cd("« HOME »", 3));
		else if (find_var_env(env, "HOME=")[5] == '\0')
			return (ft_strdup(""));
		else if (test_cd_home(args, env, stats))
			return (error_cd(&find_var_env(env, "HOME=")[5],
						test_cd_home(args, env, stats)));
	}
	return (NULL);
}
