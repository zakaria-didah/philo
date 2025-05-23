/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:20:55 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/20 22:57:42 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

size_t	list_len_(t_garb *head)
{
	size_t	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	*add_garb(void *ptr)
{
	t_garb	*node;
	t_garb	**head;

	node = malloc(sizeof(t_garb));
	node->ptr = ptr;
	node->prev = NULL;
	node->next = NULL;
	head = _get_head();
	if (!*head)
		(*head) = node;
	else
	{
		node->prev = NULL;
		node->next = *head;
		(*head)->prev = node;
		*head = node;
	}
	return (ptr);
}

void	ft_free(void)
{
	t_garb	*tmp;
	t_garb	*head;

	head = *_get_head();
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->ptr);
		free(tmp);
	}
	dealloc_arena();
}

t_garb	**_get_head(void)
{
	static t_garb	*head = NULL;

	return (&head);
}
t_mem *_get_last_(t_mem *head)
{
	t_mem	*last;

	last = head;
	while (last && last->next)
		last = last->next;
	return (last);
}
