/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdidah <zdidah@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:20:21 by zdidah            #+#    #+#             */
/*   Updated: 2025/05/27 23:40:04 by zdidah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (const char *)src;
	if (s < d)
	{
		while (len--)
		{
			*(d + len) = *(s + len);
		}
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}
