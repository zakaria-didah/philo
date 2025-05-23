/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:55:54 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/21 09:21:07 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garb.h"

t_mem	**parena_head(void)
{
	static t_mem	*mem = NULL;

	if (!mem)
	{
		mem = malloc(sizeof(t_mem));
		mem->offset = 0;
		mem->size = ARENA_SIZE;
		mem->mempool = malloc(mem->size);
		ft_bzero(mem->mempool, mem->size);
		mem->next = NULL;
	}
	return (&mem);
}

void	reset_arena(void)
{
	t_mem	*mem;
	t_mem	*tmp;

	mem = *arena_head();
	if (mem)
	{
		ft_bzero(mem->mempool, mem->size);
		mem->offset = 0;
	}
	tmp = mem;
	if (mem->next)
		clear_arena(mem->next);
	tmp->next = NULL;
}

int	clear_arena(t_mem *mem)
{
	t_mem	*tmp;

	tmp = NULL;
	if (!mem)
		mem = *arena_head();
	while (mem)
	{
		free(mem->mempool);
		tmp = mem;
		mem = mem->next;
		free(tmp);
	}
	return (1);
}

t_mem	*realloc_arena(t_mem **head)
{
	t_mem	*arena;
	t_mem	*new;

	new = malloc(sizeof(t_mem));
	arena = _get_last_(*head);
	new->size = arena->size * 2;
	new->mempool = malloc(new->size);
	ft_bzero(new->mempool, new->size);
	new->offset = 0;
	new->next = NULL;
	arena->next = new;
	return (new);
}

void	dealloc_arena(void)
{
	t_mem	*alloc;
	t_mem	*tmp;

	alloc = *arena_head();
	while (alloc)
	{
		free(alloc->mempool);
		tmp = alloc;
		alloc = alloc->next;
		free(tmp);
	}
	alloc = *parena_head();
	while (alloc)
	{
		free(alloc->mempool);
		tmp = alloc;
		alloc = alloc->next;
		free(tmp);
	}
}
