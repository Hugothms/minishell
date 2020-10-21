/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/21 19:57:12 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Takes as a parameter an element and frees the memory of
**  the element’s content.
** @param lst	The adress of a pointer to an element.
*/

void			c_lst_free_one(t_list_cmd *lst)
{
	if (!lst)
		return ;
	if (lst->str)
		free(lst->str);
	free(lst);
}

void			c_lst_remove_next_one(t_list_cmd *lst)
{
	t_list_cmd	*tmp;

	if (!lst || !lst->next)
		return ;
	tmp = lst->next->next;
	c_lst_free_one(lst->next);
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

void			c_lst_clear(t_list_cmd *lst)
{
	if (!lst)
		return ;
	if ((lst)->next)
		c_lst_clear((lst)->next);
	c_lst_free_one(lst);
	lst = NULL;
}

/*
** Iterates the list ’lst’ and applies the function ’f’ to the content of each
**  element.
** @param lst	The adress of a pointer to an element.
** @param f		The adress of the function used to iterate on the list.
*/

void			c_lst_iter(t_list_cmd *lst, void (*f)(void *))
{
	t_list_cmd	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp->next)
	{
		f(tmp->str);
		tmp = tmp->next;
	}
	f(tmp->str);
}

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

t_list_cmd		*c_lst_map(t_list_cmd *lst, void *(*f)(void *))
{
	t_list_cmd	*tmp;
	t_list_cmd	*new;
	t_list_cmd	*mapedlst;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	if (!(mapedlst = c_lst_new(f(tmp->str), tmp->flags)))
		c_lst_clear(mapedlst);
	tmp = tmp->next;
	while (tmp)
	{
		if (!(new = c_lst_new(f(tmp->str), tmp->flags)))
			c_lst_clear(mapedlst);
		c_lst_add_back(&mapedlst, new);
		tmp = tmp->next;
	}
	return (mapedlst);
}
