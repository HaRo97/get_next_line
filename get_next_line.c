#include "get_next_line.h"



char    *fill_buffer(int fd, char *buffer)
{
    // Read buff_size byts from fd to stash
    int found_endline;
    long bytes_read = 0;
    char *stash;
    // size_t j;

    found_endline = 0;
    stash = malloc(BUFFER_SIZE + 1);
    if (!stash)
        return (NULL);
    while (found_endline == 0)
    {
        if ((bytes_read = read(fd, stash, BUFFER_SIZE)) == -1)
        {
//           // printf("\n------- read failed -------\n\n");
            free(stash);
            return (NULL);
        }
//         else if(bytes_read == 0)
//         {
// //            // printf("\n------- 0 bytes read -------\n\n");
//             free(stash);
//             return (NULL);
//         }
        else
        {
            stash[bytes_read] = '\0';
//            // printf("\n-------stash : %s\n\n", stash);
            buffer = ft_strjoin(buffer, stash);
            if (bytes_read < BUFFER_SIZE)
                break;
            if (ft_strchr(stash, '\n'))
                found_endline = 1;
        }
    }
//    printf("bytes read : %ld\n", bytes_read);
    free(stash);
//    printf("buffer : %s\n\n", buffer);
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
        // if(buffer[j] == "\0")
        //     free(buffer);
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

    // Return NULL if there is nothing else to read or an error occured.
    if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    // If there is no '\n' in the buffer --> Read from the fd, BUFFER_SIZE bytes and strjoin them in buffer. Stop after you find '\n'.
    // buffer = NULL;
    buffer = fill_buffer(fd, buffer);
    if(buffer == NULL)
        return (NULL);
    
    k = ft_strlen(buffer);
    // Copy bytes untill '\n' from buffer to line 
    i = 0;
    line = ft_get_line(buffer, &i);
//    printf("i : %zu\n", i);
    // Clean buffer and take bytes after '\n', if there are, in the beginning of buffer.
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
    if(k == 0)
        free(buffer);
    // printf("buffer : %s\n\n", buffer);
    return (line);
}



int main()
{
    char *str;
    int fd = open("text.txt", O_RDONLY);
//    char *buffer;
    int i = 0;
    while(i < 12)
    {
        str = get_next_line(fd);
        // if(!str)
        //     break;
        printf("line : %s\n\n--------------------------------------------------------------------------------------------------------------------------\n\n", str);
        // free(str);
        i++;
        system("leaks a.out");
    }
    // printf("%s\n",get_next_line(fd));
}
