/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:45 by adrgutie          #+#    #+#             */
/*   Updated: 2024/08/17 21:40:27 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftnop.h"

int	ft_isdigit(int c)
{
	if (47 < c && c < 58)
		return (1);
	return (0);
}

// int main()
// {
// 	int a;
// 	a = -1;
// 	while (++a < 1000000)
// 	{
// 		if (ft_isdigit(a) != isdigit(a))
// 			printf("Huh?, this is where it went wrong %d\n", a);
// 		else
// 			printf("%d, Ok!\n", a);
// 	}
// }