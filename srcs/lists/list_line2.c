/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoreau <vmoreau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/12/07 12:47:01 by vmoreau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Takes as a parameter an element and frees the memory of
**  the element’s content.
** @param lst	The adress of a pointer to an element.
*/

void			l_lst_free_one(t_list_line *lst)
{
	if (!lst)
		return ;
	if (lst->cmd)
		c_lst_clear(lst->cmd);
	free(lst);
}

void			l_lst_remove_next_one(t_list_line *lst)
{
	t_list_line	*tmp;

	if (!lst || !lst->next)
		return ;
	tmp = lst->next->next;
	l_lst_free_one(lst->next);
	lst->next = tmp;
}

/*
** Deletes and frees the given element and every successor of that element,
**  using the function ’del’ and free(3).
** Finally, the pointer to the list must be set to NULL.
** @param lst	The adress of a pointer to an element.
** @param del	The adress of the function used to delete the content of the
**  element.
*/

void			l_lst_clear(t_list_line *lst)
{
	if (!lst)
		return ;
	if (lst->next)
	{
		l_lst_clear(lst->next);
	}
	l_lst_free_one(lst);
	lst = NULL;
}

t_list_line		*l_lst_copy_all(t_list_cmd *cmd)
{
	t_list_cmd	*new_cmd;
	t_list_line	*new_line;

	new_cmd = NULL;
	new_line = NULL;
	while (cmd)
	{
		c_lst_add_back(&new_cmd, c_lst_new(cmd->str, cmd->flags));
		cmd = cmd->next;
	}
	l_lst_add_back(&new_line, l_lst_new(new_cmd));
	return (new_line);
}
