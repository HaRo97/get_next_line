#include "get_next_line.h"



char    *fill_buffer(int fd, char *buffer)
{
    // Read buff_size byts from fd to stash
    int found_endline;
    long bytes_read = 0;
    char *stash;
    size_t j;

    found_endline = 0;
    stash = malloc(BUFFER_SIZE + 1);
    if (!stash)
        return (NULL);
    while (found_endline == 0)
    {
        if ((bytes_read = read(fd, stash, BUFFER_SIZE)) == -1)
        {
            free(stash);
            return (NULL);
        }
        else if(bytes_read == 0)
        {
            free(stash);
            return (buffer);
        }
        else
        {
            stash[bytes_read] = '\0';
            // buffer = ft_strjoin(buffer, stash);
            j = ft_strlen(buffer);
            ft_strlcat(buffer, stash, j + bytes_read);
            // if(buffer == NULL)
            // {
            //     free(buffer);
            //     return (NULL);
            // }
            if (bytes_read < BUFFER_SIZE)
                break;
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
    if(ft_strchr(buffer, '\n'))
        (*i)++;
    line = malloc(*i + 1);
    if (!line)
        return NULL;
    while (j < *i)
    {
        line[j] = buffer[j];
        j++;
    }
    // if (ft_strchr(buffer, '\n'))
    // {
    //     line[j] = buffer[j];
    //     line[++j] = '\0';
    // }
    // else
        line[j] = '\0';
    return (line);
}

char *get_next_line(int fd)
{
    static char *buffer; 
    char *line;
    size_t i;
    size_t j;

    // Return NULL if there is nothing else to read or an error occured.
    if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    buffer = NULL;
    // If there is no '\n' in the buffer --> Read from the fd, BUFFER_SIZE bytes and strjoin them in buffer. Stop after you find '\n'.
    buffer = fill_buffer(fd, buffer);
    if(buffer == NULL)
        return (NULL);
    

    // Copy bytes untill '\n' from buffer to line 
    i = 0;
    line = ft_get_line(buffer, &i);
    
    // Clean buffer and take bytes after '\n', if there are, in the beginning of buffer.
    j = 0;
    if(i < ft_strlen(buffer))
    {
        while (buffer[i])
            buffer[j++] = buffer[i++];
    }   
    buffer[j] = '\0';

    // printf("buffer : %s\n\n", buffer);

    return (line);
}



// int main()
// {
//     // char *str;
//     int fd = open("text.txt", O_RDONLY);
// //    char *buffer;
//     // int i = 0;
//     // while(i < 12)
//     // {
//     //     str = get_next_line(fd);
//     //     // if(!str)
//     //     //     break;
//     //     printf("line : %s\n-------------------------------\n\n", str);
//     //     free(str);
//     //     i++;
//     //     system("leaks a.out");
//     // }
//     printf("%s\n",get_next_line(fd));
// }
