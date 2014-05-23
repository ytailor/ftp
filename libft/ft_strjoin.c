/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytailor <ytailor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 18:03:44 by ytailor           #+#    #+#             */
/*   Updated: 2014/04/14 18:03:53 by ytailor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*ret;
	size_t		len;

	len = (ft_strlen(s1) + ft_strlen(s2));
	if ((ret = (ft_strnew(len))) == NULL)
		return (NULL);
	ft_strncat(ret, s1, ft_strlen(s1));
	ft_strncat(ret, s2, ft_strlen(s2));
	return (ret);
}
