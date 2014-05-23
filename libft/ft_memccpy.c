/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 14:39:53 by ytailor           #+#    #+#             */
/*   Updated: 2014/04/14 18:05:58 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char			*dest;
	const char		*src;
	unsigned char	ch;

	dest = s1;
	src = s2;
	ch = c;
	while (n > 0 && *src != ch)
	{
		*dest = *src;
		n--;
		dest++;
		src++;
	}
	if (n == 0)
		return (NULL);
	*dest = *src;
	return (dest + 1);
}
