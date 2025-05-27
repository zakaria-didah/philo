/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 22:52:19 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/27 23:41:16 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_H
#define VECTOR_H


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garb/garb.h"

#define INITIAL_CAPACITY 4

typedef struct s_vector
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	element_size;

	void	(*push_back)(struct s_vector *, const void *);
	void	(*pop_back)(struct s_vector *);
	void	*(*get)(struct s_vector *, size_t index);
	void	(*set)(struct s_vector *, size_t index, const void *);
	void	(*destroy)(struct s_vector *);
}			t_vector;

t_vector		*vector_new(size_t element_size);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif