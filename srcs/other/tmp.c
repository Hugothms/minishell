/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:11:59 by vmoreau           #+#    #+#             */
/*   Updated: 2020/12/07 15:12:21 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			free_cmd(void *lst)
{
	t_list_cmd	*tmp;

	tmp = lst;
	free(tmp->str);
	free(tmp);
}

void			ft_lstremove_next_one(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !lst->next)
		return ;
	tmp = lst->next->next;
	del(lst->next);
	lst->next = tmp;
}
