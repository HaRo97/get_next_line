#include "get_next_line.h"



char    *fill_buffer(int fd, char *buffer)
{
    int found_endline;
    int found_EOF;
    long bytes_read = 0;
    char *stash;

    found_endline = 0;
    found_EOF = 0;
    stash = malloc(BUFFER_SIZE + 1);
    if (!stash)
        return (NULL);
    while (found_endline == 0 && found_EOF == 0)
    {
        if ((bytes_read = read(fd, stash, BUFFER_SIZE)) == -1)
        {
            free(stash);
            free(buffer);
            return (NULL);
        }
        else if(bytes_read == 0)
            break;
        else
        {
            if (bytes_read < BUFFER_SIZE)
                found_EOF = 1;
            stash[bytes_read] = '\0';
            buffer = ft_strjoin(buffer, stash);
            if (ft_strchr(stash, '\n'))
                found_endline = 1;
        }
    }
    free(stash);
    return (buffer);
}

char *ft_get_line(char *buffer, size_t *i)
{
    size_t j = 0;
    char *line;

    while(buffer[*i] != '\n' && buffer[*i] != '\0')
        (*i)++;
    if(buffer[*i] == '\n')
        (*i)++;
    line = malloc(*i + 1);
    if (!line)
        return NULL;
    while (j < *i)
    {
        line[j] = buffer[j];
        j++;
    }
        line[j] = '\0';
    return (line);
}

char *get_next_line(int fd)
{
    static char *buffer; 
    char *line;
    size_t i;
    size_t j;
    size_t k;

    if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    buffer = fill_buffer(fd, buffer);
    if(buffer == NULL)
    {
        free(buffer);
        return (NULL);
    }
    k = ft_strlen(buffer);
        i = 0;
        line = ft_get_line(buffer, &i);
    j = 0;
    if(i < k)
    {
        while (buffer[i])
            buffer[j++] = buffer[i++];
    }   
    buffer[j] = '\0';
    if (line[0] == '\0')
    {
        free(line);
        return (NULL);
    }
    return (line);
}



// int main()
// {
//     char *str;
//     int fd = open("text.txt", O_RDONLY);
// //    char *buffer;
//     int i = 0;
//     // while(i < 12)
//     // {
//     //     // if(!str)
//     //     //     break;
//     //     printf("line : %s\n\n------------------------------------------------------\n\n", str);
//     //     free(str);
//     //     i++;
//     // }
//         system("leaks a.out");
//     // printf("%s\n",get_next_line(fd));
// }
