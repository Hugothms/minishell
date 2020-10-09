/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/09 12:12:13 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Takes as a parameter an element and frees the memory of
**  the element’s content.
** @param lst	The adress of a pointer to an element.
*/

void			l_lst_free_one(void *lst)
{
	t_list_line	*tmp;

	tmp = lst;
	c_lst_free_one(tmp->cmd);
	free(tmp);
}

void			l_lst_remove_next_one(t_list_line *lst, void (*del)(void*))
{
	t_list_line	*tmp;

	if (!lst || !lst->next)
		return ;
	tmp = lst->next->next;
	del(lst->next);
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

void			l_lst_del_one(t_list_line *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst);
}

/*
** Deletes and frees the given element and every successor of that element,
**  using the function ’del’ and free(3).
** Finally, the pointer to the list must be set to NULL.
** @param lst	The adress of a pointer to an element.
** @param del	The adress of the function used to delete the content of the
**  element.
*/

void			l_lst_clear(t_list_line **alst, void (*del)(void*))
{
	if (!*alst)
		return ;
	if ((*alst)->next)
	{
		l_lst_clear(&((*alst)->next), del);
		free((*alst)->next);
	}
	l_lst_del_one(*alst, del);
	*alst = NULL;
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
// 							void (*del)(void *))
// {
// 	t_list_line	*tmp;
// 	t_list_line	*new;
// 	t_list_line	*mapedlst;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	tmp = lst;
// 	if (!(mapedlst = l_lst_new(f(tmp->str), tmp->flags)))
// 		l_lst_clear(&mapedlst, del);
// 	tmp = tmp->next;
// 	while (tmp)
// 	{
// 		if (!(new = l_lst_new(f(tmp->str), tmp->flags)))
// 			l_lst_clear(&mapedlst, del);
// 		l_lst_add_back(&mapedlst, new);
// 		tmp = tmp->next;
// 	}
// 	return (mapedlst);
// }
