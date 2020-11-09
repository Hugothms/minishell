/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:38 by vmoreau           #+#    #+#             */
/*   Updated: 2020/11/09 11:58:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(int *exit_status)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	ret = ft_strjoin_free(ret, "\n");
	return (ret);
}
