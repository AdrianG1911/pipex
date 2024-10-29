/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:21:52 by adrgutie          #+#    #+#             */
/*   Updated: 2024/08/17 20:44:53 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftnop.h"

int	ft_toupper(int c)
{
	if (96 < c && c < 123)
		c -= 32;
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main()
// {
// 	int	a;
// 	a = -1;
// 	while (++a < 350)
// 	{
// 		if (ft_toupper(a) != toupper(a))
// 		{
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 			printf("%d, %d\n", ft_toupper(a), toupper(a));
// 		}
// 	}

// }
