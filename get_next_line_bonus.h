/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:13:18 by hrochd            #+#    #+#             */
/*   Updated: 2024/03/26 03:22:06 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

typedef struct s_info
{
	char	*buffer;
	char	*stash;
	int		bytes_read;
	int		found_endline;
}			t_info;

size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
int		ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char **s1, char *s2);
char	*ft_get_line(char *stash, size_t *i);
void	shift_stash(char **stash, size_t i);
char	*get_next_line(int fd);

#endif