#include "../includes/minishell.h"

void			free_cmd(void *lst)
{
	t_word	*tmp;

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