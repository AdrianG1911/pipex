/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:19:45 by adrgutie          #+#    #+#             */
/*   Updated: 2024/08/17 21:40:27 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftnop.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb && SIZE_MAX / nmemb < size)
	{
		return (NULL);
	}
	p = malloc(nmemb * size);
	if (p)
		ft_memset(p, 0, nmemb * size);
	return (p);
}

// int	main()
// {
// 	char *a;
// 	char *b;

// 	a = ft_calloc(0,0);
// 	b = calloc(0,0);
// 	if (b == NULL)
// 		printf("calloc returned NULL");
// 	if (a != b)
// 		printf("%p, %p\n", a, b);
// 	printf("show me");
// }