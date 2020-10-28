/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:16:38 by vmoreau           #+#    #+#             */
/*   Updated: 2020/10/28 15:10:51 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	ret = ft_strjoin_free(ret, "\n");
	return (ret);
}
