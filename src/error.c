/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:10:58 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/05 19:58:02 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	memerror(int error)
{
	if (error == ENOMEM)
		ft_putstr_fd("error: not enough memory\n", STDERR_FILENO);
	else
		ft_putstr_fd("", STDERR_FILENO);
	return (1);
}
