/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:48:36 by hthomas           #+#    #+#             */
/*   Updated: 2020/10/08 15:26:17 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Allocates (with malloc(3)) and returns a new element.
** The variable ’content’ is initialized with the value of the
**  parameter ’content’. The variable ’next’ is initialized to NULL.
** @param str	The str to create the new element with
** @param type	The type to create the new element with
** @return			The new element
*/

t_cmd	*c_lst_new(char *str, char type)
{
	t_cmd	*new;

	if (!(new = malloc(sizeof(t_cmd))))
		return (NULL);
	new->str = ft_strdup(str);
	new->flags = type;
	new->next = NULL;
	return (new);
}

/*
** Adds the element ’new’ at the beginning of the list
** @param alst	The address of a pointer to the first link of a list
** @param new	The address of a pointer to the element to be added to the list
*/

void			c_lst_add_front(t_cmd **alst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *alst;
	*alst = new;
	new->next = tmp;
}

/*
** Counts the number of elements in a list
** @param lst	The beginning of the list
** @return		Length of the list
*/

int				c_lst_size(t_cmd *lst)
{
	int				cpt;
	t_cmd	*pt;

	if (!lst)
		return (0);
	cpt = 1;
	pt = lst;
	while ((pt = pt->next))
		cpt++;
	return (cpt);
}

/*
** Returns the last element of the list
** @param lst	The beginning of the list
** @return		Last element of the list
*/

t_cmd	*c_lst_last(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/*
** Adds the element ’new’ at the end of the list
** @param alst	The address of a pointer to the first link of a list.
** @param new	The address of a pointer to the element to be added to the list.
*/

void			c_lst_add_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*pt;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	pt = *alst;
	while (pt->next)
		pt = pt->next;
	pt->next = new;
}
