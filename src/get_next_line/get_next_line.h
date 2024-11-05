/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:37:13 by adrgutie          #+#    #+#             */
/*   Updated: 2024/11/05 19:59:12 by adrgutie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

# define BUFFER_SIZE 42
# define CLEAR_MEM -100

char	*get_next_line(int fd);
char	*free_ft_strjoin(char **s1, char **s2);
char	*free_ft_substr(char **s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	freeptr(char **p1, char **p2, char **p3);
#endif