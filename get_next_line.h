#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000000
#endif

size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
int ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char **s1, char *s2);
char *ft_get_line(char *stash, size_t *i);
void shift_stash(char **stash, size_t i);
char *get_next_line(int fd);


#endif