/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:21:52 by adrgutie          #+#    #+#             */
/*   Updated: 2024/08/17 21:40:27 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftnop.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		if (s1[i] == 0)
			break ;
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char *argv[])
// {
// 	if (argc > 1)
// 	{
// 		char *h = argv[1];
// 		char *n = argv[2];
// 		int	e = 4;
// 		if (ft_strncmp(h, n, e) != strncmp(h, n, e))
// 		{
// 			printf("NOOOOO");
// 		}
// 		printf("%d, %d\n", ft_strncmp(h, n, e), strncmp(h, n, e));
// 	}
// }