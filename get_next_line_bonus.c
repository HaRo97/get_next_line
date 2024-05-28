/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrochd <hrochd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:12:56 by hrochd            #+#    #+#             */
/*   Updated: 2024/04/28 10:21:34 by hrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char **s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (*s1 == NULL && s2 == NULL)
		return (NULL);
	else if (*s1 == NULL && s2)
		return (ft_strdup(s2));
	else if (s2 == NULL && *s1)
		return (*s1);
	else
	{
		i = ft_strlen(*s1);
		j = ft_strlen(s2);
		p = malloc((i + j + 1) * sizeof(char));
		if (!p)
			return (free(*s1), *s1 = NULL, NULL);
		ft_strlcpy(p, *s1, (i + 1));
		ft_strlcat(p, s2, (i + j + 1));
		free(*s1);
		*s1 = NULL;
	}
	return (p);
}

char	*fill_stash(int fd, int *read_failed)
{
	t_info	f;

	((1) && (f.stash = NULL, f.found_endline = 0, f.bytes_read = 1));
	while (f.found_endline == 0 && f.bytes_read > 0)
	{
		f.buffer = malloc((unsigned int)BUFFER_SIZE + 1);
		if (!f.buffer)
			return (free(f.stash), f.stash = NULL, *read_failed = 1, NULL);
		f.bytes_read = read(fd, f.buffer, BUFFER_SIZE);
		if (f.bytes_read <= 0)
		{
			free(f.buffer);
			break ;
		}
		f.buffer[f.bytes_read] = '\0';
		if (ft_strchr(f.buffer, '\n'))
			f.found_endline = 1;
		f.stash = ft_strjoin(&f.stash, f.buffer);
		free(f.buffer);
	}
	if (f.bytes_read == 0 && f.stash && !*f.stash)
		((1) && (free(f.stash), f.stash = NULL, *read_failed = 0));
	if (f.bytes_read == -1)
		return (*read_failed = 1, NULL);
	return (f.stash);
}

char	*ft_get_line(char *stash, size_t *i)
{
	char	*line;

	if (!stash)
		return (NULL);
	while (stash[*i] != '\0' && stash[*i] != '\n')
		(*i)++;
	if (stash[*i] == '\n')
		(*i)++;
	line = malloc(*i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, *i + 1);
	return (line);
}

void	shift_stash(char **stash, size_t i)
{
	char	*shifted_stash;

	shifted_stash = NULL;
	if (*stash == NULL)
		return ;
	else
	{
		if (*(*stash + i) != '\0')
			shifted_stash = ft_strdup(((*stash) + i));
		free((*stash));
		(*stash) = shifted_stash;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;
	char		*h;
	int			read_failed;
	size_t		i;

	read_failed = 0;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 0)
		return (NULL);
	if (ft_strchr(stash[fd], '\n') > 0)
	{
		((1) && (i = 0, line = ft_get_line(stash[fd], &i)));
		if (!line)
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		return (shift_stash(&stash[fd], i), line);
	}
	h = fill_stash(fd, &read_failed);
	if (!h && read_failed == 1)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = ft_strjoin(&stash[fd], h);
	(free(h), i = 0);
	line = ft_get_line(stash[fd], &i);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	return (shift_stash(&stash[fd], i), line);
}
