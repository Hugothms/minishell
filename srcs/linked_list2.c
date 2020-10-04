/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/04 16:26:09 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Takes as a parameter an element and frees the memory of 
** the element’s content using the function ’del’ given as a parameter 
** and free the element. The memory of ’next’ must not be freed
** @param lst	The adress of a pointer to an element.
** @param del	The adress of the function used to delete the content of the 
**				element.
*/
void	c_lstdelone(t_list_command *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->str);
	free(lst);
}

/*
** Deletes and frees the given element and every successor of that element, 
** using the function ’del’ and free(3).
** Finally, the pointer to the list must be set to NULL.
** @param lst	The adress of a pointer to an element.
** @param del	The adress of the function used to delete the content of the 
** element.
*/
void	c_lstclear(t_list_command **alst, void (*del)(void*))
{
	if (!*alst)
		return ;
	if ((*alst)->next)
	{
		c_lstclear(&((*alst)->next), del);
		free((*alst)->next);
	}
	c_lstdelone(*alst, del);
}

/*
** Iterates the list ’lst’ and applies the function ’f’ to the content of each 
** element.
** @param lst	The adress of a pointer to an element.
** @param f		The adress of the function used to iterate on the list.
*/
void	c_lstiter(t_list_command *lst, void (*f)(void *))
{
	t_list_command	*tmp;

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
** element. Creates a newlist resulting of the successive applications of the 
** function ’f’. The ’del’ function is used to delete the content of an 
** element if needed.
** @param lst	The adress of a pointer to an element.
** @param f		The adress of the function used to iterate on the list.
** @param del	The adress of the function used to delete the content of an 
*** element if needed.
** @return		The new list. NULL if the allocation fails.
*/
t_list_command	*c_lstmap(t_list_command *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_command	*tmp;
	t_list_command	*new;
	t_list_command	*mapedlst;

	if (!lst || !f || !del)
		return (NULL);
	tmp = lst;
	if (!(mapedlst = c_lstnew(f(tmp->str), tmp->flags)))
		c_lstclear(&mapedlst, del);
	tmp = tmp->next;
	while (tmp)
	{
		if (!(new = c_lstnew(f(tmp->str), tmp->flags)))
			c_lstclear(&mapedlst, del);
		c_lstadd_back(&mapedlst, new);
		tmp = tmp->next;
	}
	return (mapedlst);
}
