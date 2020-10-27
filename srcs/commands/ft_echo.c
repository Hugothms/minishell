/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:29 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/27 16:45:08 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_echo(t_list_cmd *args)
{
	int		nflag;
	char	*ret;

	nflag = 0;
	if (!args || !args->str)
		return (ft_strdup("\n"));
	while (!ft_strcmp(args->str, "-n"))
	{
		nflag = 1;
		args = args->next;
	}
	ret = ft_strdup("");
	while (args)
	{
		ret = ft_strjoin_free(ret, args->str);
		if (args->next && !(args->flags & F_NO_SP_AFTER))
			ret = ft_strjoin_free(ret, " ");
		args = args->next;
	}
	if (!nflag)
		ret = ft_strjoin_free(ret, "\n");
	return (ret);
}