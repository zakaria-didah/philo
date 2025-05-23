/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:32:49 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/21 09:31:25 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARB_H
# define GARB_H

# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define CHUNK 64
# define ARENA_SIZE 10240

# define C_ARENA 0x01
# define C_PARENA 0x02
# define C_MALLOC 0x04
# define C_TRACK 0x08

typedef struct s_mem
{
	size_t			offset;
	size_t			size;
	char			*mempool;
	struct s_mem	*next;
}					t_mem;

typedef struct s_garb
{
	void			*ptr;
	struct s_garb	*prev;
	struct s_garb	*next;
}					t_garb;

void				ft_remove(void *ptr);
void				_link_list(t_garb *node);
t_garb				**_get_head(void);
void				*add_garb(void *ptr);
void				*ft_calloc(size_t size, int cflag);
void				ft_free(void);
size_t				list_len_(t_garb *head);
t_mem				**arena_head(void);
t_mem				*realloc_arena(t_mem **head);
void				dealloc_arena(void);
void				reset_arena(void);
int					clear_arena(t_mem *alloc);
int					gc_mode(int mode);
t_mem				**parena_head(void);
t_mem				*_get_last_(t_mem *head);
void				ft_bzero(void *s, size_t n);
#endif
