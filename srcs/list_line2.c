/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/11 13:32:05 by hthomas          ###   ########.fr       */
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
** Takes as a parameter an element and frees the memory of
**  the element’s content using the function ’del’ given as a parameter
**  and free the element. The memory of ’next’ must not be freed
** @param lst	The adress of a pointer to an element.
** @param del	The adress of the function used to delete the content of the
**	 			element.
*/

void			l_lst_del_one(t_list_line *lst)
{
	if (!lst)
		return ;
	l_lst_free_one(lst);
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
		// free((lst)->next);
	}
	l_lst_del_one(lst);
	lst = NULL;
}

/*
** Iterates the list ’lst’ and applies the function ’f’ to the content of each
**  element.
** @param lst	The adress of a pointer to an element.
** @param f		The adress of the function used to iterate on the list.
*/

// void			l_lst_iter(t_list_line *lst, void (*f)(void *))
// {
// 	t_list_line	*tmp;

// 	if (!lst)
// 		return ;
// 	tmp = lst;
// 	while (tmp->next)
// 	{
// 		f(tmp->str);
// 		tmp = tmp->next;
// 	}
// 	f(tmp->str);
// }

/*
** Iterates the list ’lst’ and applies the function ’f’ to the content of each
**  element. Creates a newlist resulting of the successive applications of the
**  function ’f’. The ’del’ function is used to delete the content of an
**  element if needed.
** @param lst	The adress of a pointer to an element.
** @param f		The adress of the function used to iterate on the list.
** @param del	The adress of the function used to delete the content of an
** element if needed.
** @return		The new list. NULL if the allocation fails.
*/

// t_list_line	*l_lst_map(t_list_line *lst, void *(*f)(void *),\
// 							void (*l_lst_free_one)(void *))
// {
// 	t_list_line	*tmp;
// 	t_list_line	*new;
// 	t_list_line	*mapedlst;

// 	if (!lst || !f || !l_lst_free_one)
// 		return (NULL);
// 	tmp = lst;
// 	if (!(mapedlst = l_lst_new(f(tmp->str), tmp->flags)))
// 		l_lst_clear(&mapedlst, l_lst_free_one);
// 	tmp = tmp->next;
// 	while (tmp)
// 	{
// 		if (!(new = l_lst_new(f(tmp->str), tmp->flags)))
// 			l_lst_clear(&mapedlst, l_lst_free_one);
// 		l_lst_add_back(&mapedlst, new);
// 		tmp = tmp->next;
// 	}
// 	return (mapedlst);
// }

t_list_line		*l_lst_copy_all(t_list_cmd *cmd, char separator)
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
	l_lst_add_back(&new_line, l_lst_new(new_cmd, separator));		
}
