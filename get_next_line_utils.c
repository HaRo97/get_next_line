#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;
	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
		i++;
	return (i);
}



size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (slen);
	dlen = ft_strlen(dst);
	if (dlen >= dstsize)
		return (slen + dstsize);
	if (dlen < dstsize)
		ft_strlcpy(dst + dlen, src, dstsize - dlen);
	return (dlen + slen);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	slen;
	char	*s2;

	i = 0;
	if (!s1)
		return (NULL);
	slen = ft_strlen(s1) + 1;
	s2 = malloc(slen * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, slen);
	return (s2);
}

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

int ft_strchr(char *s, int c)
{
	int	i;
	int count;

	if (s == NULL)
		return (-1);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			count++;
		i++;
	}
	return (count);
}
// char *f(char *str)
// {
// 	if (!str)
// 		return (NULL);
// 	return (free(str), NULL);
// }
