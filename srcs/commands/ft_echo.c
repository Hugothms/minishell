/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:29 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/04 17:32:25 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_nflag(char *str)
{
	int i;

	i = 1;
	if (!ft_strncmp(str, "-n", 2))
	{
		while (str[i] == 'n')
			i++;
		if (str[i] != '\0')
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

char	*ft_echo(t_list_cmd *args)
{
	int		nflag;
	char	*ret;

	nflag = 0;
	if (!args || !args->str)
		return (ft_strdup("\n"));
	while (args && check_nflag(args->str))
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
