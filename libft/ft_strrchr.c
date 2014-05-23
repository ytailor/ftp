/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 12:27:41 by ytailor           #+#    #+#             */
/*   Updated: 2014/04/14 18:09:57 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	ch;

	size = ft_strlen((char *)s);
	ch = c;
	while (size > 0)
	{
		if (s[size] == ch)
			return ((char *)&s[size]);
		size--;
	}
	if (s[size] == ch)
		return ((char *)&s[size]);
	return (NULL);
}
