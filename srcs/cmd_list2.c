/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:07:33 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/08 17:46:40 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Takes as a parameter an element and frees the memory of
**  the element’s content.
** @param lst	The adress of a pointer to an element.
*/

// void			ft_list_free_one(void *lst)
// {
// 	t_list	*tmp;

// 	tmp = lst;
// 	free(tmp->str);
// 	free(tmp);
// }

void			ft_list_remove_next_one(t_list *lst, void (*del)(void*))
{
	t_list	*tmp;

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

void			ft_list_del_one(t_list *lst, void (*del)(void*))
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

void			ft_list_clear(t_list **alst, void (*del)(void*))
{
	if (!*alst)
		return ;
	if ((*alst)->next)
	{
		ft_list_clear(&((*alst)->next), del);
		free((*alst)->next);
	}
	ft_list_del_one(*alst, del);
	*alst = NULL;
}

/*
** Iterates the list ’lst’ and applies the function ’f’ to the content of each
**  element.
** @param lst	The adress of a pointer to an element.
** @param f		The adress of the function used to iterate on the list.
*/

// void			ft_list_iter(t_list *lst, void (*f)(void *))
// {
// 	t_list	*tmp;

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

// t_list	*ft_list_map(t_list *lst, void *(*f)(void *),\
// 							void (*del)(void *))
// {
// 	t_list	*tmp;
// 	t_list	*new;
// 	t_list	*mapedlst;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	tmp = lst;
// 	if (!(mapedlst = ft_list_new(f(tmp->str), tmp->flags)))
// 		ft_list_clear(&mapedlst, del);
// 	tmp = tmp->next;
// 	while (tmp)
// 	{
// 		if (!(new = ft_list_new(f(tmp->str), tmp->flags)))
// 			ft_list_clear(&mapedlst, del);
// 		ft_list_add_back(&mapedlst, new);
// 		tmp = tmp->next;
// 	}
// 	return (mapedlst);
// }
