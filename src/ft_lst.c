/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuezeri <chuezeri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:35:25 by chuezeri          #+#    #+#             */
/*   Updated: 2025/05/08 15:54:29 by chuezeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list *ft_lstnew(void *content)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp;

	if (!lst || !new)
		return;
	if (!*lst)
	{
		*lst = new;
		return;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void ft_lstclear(t_list **lst)
{
	t_list *temp;

	if (!lst)
		return;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		(*lst)->content = NULL;
		(*lst)->next = NULL;
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
