/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:43:28 by adrgutie          #+#    #+#             */
/*   Updated: 2024/08/17 21:40:27 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftnop.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	slen;
	char			*result;

	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	result = (char *)malloc(slen + 1);
	if (!result)
		return (NULL);
	result[slen] = 0;
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
