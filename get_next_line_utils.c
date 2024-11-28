/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 22:48:36 by toto              #+#    #+#             */
/*   Updated: 2024/11/28 15:16:12 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


t_stash	*ft_lstnew(void *content)
{
	t_stash	*list;
	
	list = malloc(sizeof(t_stash));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

t_stash	*ft_lstlast(t_stash *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_stash **lst, t_stash *new)
{
	t_stash	*last;
	
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclear(t_stash **lst)
{
	t_stash	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		free(*lst);
	
		*lst = temp;
	}
	lst = NULL;
}
