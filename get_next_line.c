#include "get_next_line.h"

char *fill_stash(int fd, int *read_failed)
{
    char *buffer;
    char *stash;
    int bytes_read;
    int found_endline;

    stash = NULL;
    found_endline = 0;
    bytes_read = 1;
    while(found_endline == 0 && bytes_read > 0)
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer)
            return (free(stash), stash = NULL, *read_failed = 1, NULL);
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if(bytes_read <= 0)
        {
            free(buffer);
            break;
        }
        buffer[bytes_read] = '\0';
        if(ft_strchr(buffer, '\n'))
            found_endline = 1;
        stash = ft_strjoin(&stash, buffer);
        free(buffer);
    }
    if (bytes_read == 0)
    {
        if (stash && !*stash)
        {
            free(stash);
            stash = NULL;
            *read_failed = 0;
        }
    }
    if (bytes_read == -1)
    {
        *read_failed = 1;
        return (NULL);
    }
    return (stash);
}

char *ft_get_line(char *stash, size_t *i)
{
    char *line;

    if (!stash)
        return (NULL);
    while(stash[*i] != '\0' && stash[*i] != '\n')
        (*i)++;
    if(stash[*i] == '\n')
        (*i)++;
    line = malloc(*i + 1);
    if (!line)
        return (NULL);
    ft_strlcpy(line, stash, *i + 1);
    return (line);
}

void shift_stash(char **stash, size_t i)
{
    char *shifted_stash;

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


char    *get_next_line(fd)
{
    static char *stash;
    char *line;
    char   *h;
    int read_failed;
    size_t i;

    read_failed = 0;
    if (fd < 0 || BUFFER_SIZE < 0)
        return NULL;
    if(ft_strchr(stash, '\n') > 0)
    {
        i = 0;
        line = ft_get_line(stash, &i);
        if (!line)
            return (free(stash), stash = NULL, NULL);
        shift_stash(&stash, i);
        return (line);
    }
    h = fill_stash(fd, &read_failed);
    if (!h && read_failed == 1)
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    stash = ft_strjoin(&stash, h);
    free(h);
    i = 0;
    line = ft_get_line(stash, &i);
    if (!line)
        return (free(stash), stash = NULL, NULL);
    shift_stash(&stash, i);
    return (line);
}

// int main()
// {
//     char *str;
//     int fd = open("text.txt", O_RDONLY);
//     int i = 0;
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//         str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//         str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     str= get_next_line(fd);
//     printf("%s" , str);
//     free(str);
//     // system("leaks a.out");
//     // while(i < 10)
//     // {
//     //     // get_next_line(fd);
//     //     // if(!str)
//     //     //     break;
//     //     printf("line : %s***********************\n\n", get_next_line(fd));
//     //     // free(str);
//     //     i++;
//     // }
//     // system("leaks a.out");
//     // printf("%s\n",get_next_line(fd));
// }