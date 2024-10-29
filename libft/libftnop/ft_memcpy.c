/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:29:22 by adrgutie          #+#    #+#             */
/*   Updated: 2024/08/17 21:40:27 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftnop.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc > 3)
// 	{
// 		size_t	g = atoi(argv[3]);
// 		char *dst = argv[1];
// 		char *dst2 = malloc(strlen(dst) + 1);
// 		strcpy(dst2, dst);
// 		const char *src = argv[2];
// 		printf("return: %s\n", memcpy(dst, src, g));
// 		printf("return: %s\n", ft_memcpy(dst2, src, g));
// 	}
// }