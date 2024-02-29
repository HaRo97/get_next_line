#include "get_next_line.h"



char    *fill_buffer(int fd, char *buffer)
{
    // Read buff_size byts from fd to stash
    int found_endline;
    long bytes_read = 0;
    char *stash;

    found_endline = 0;

    // printf("%lu---------------\n",buff_size + 1);
    stash = malloc(BUFFER_SIZE + 1);
    if (!stash)
        return NULL;
    while (found_endline == 0)
    {
        if ((bytes_read = read(fd, stash, BUFFER_SIZE)) == -1)
            return ((void)(free(stash)), NULL);
        else
        {
            buffer = ft_strjoin(buffer, stash);
            if (ft_strchr(stash, '\n'))
                found_endline = 1;
            else if (bytes_read < BUFFER_SIZE)
            {
                free(stash);
                break;
            }
        }
    }
    free(stash);
    return (buffer);
}

char *get_line(char *buffer, int *i)
{
    // int i = 0;
    char *line;

    while(buffer[*i] != '\n')
        (*i)++;
    line = malloc(*i + 1);
    if (!line)
        return NULL;
    *i = 0;
    while (buffer[*i] != '\n')
    {
        line[*i] = buffer[*i];
        (*i)++;
    }
    line[*i] = buffer[*i];
    line[++(*i)] = '\0';
    return (line);
}

char *get_next_line(int fd)
{
    static char *buffer; 
    char *line;
    int i;
    int j;

    // Return NULL if there is nothing else to read or an error occured.
    if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);

    // If there is no '\n' in the buffer --> Read from the fd, BUFFER_SIZE bytes and strjoin them in buffer. Stop after you find '\n'.
    buffer = fill_buffer(fd, buffer);
    if(buffer == NULL)
        return (NULL);
    

    // Copy bytes untill '\n' from buffer to line 
    i = 0;
    line = get_line(buffer, &i);

    // Clean buffer and take bytes after '\n', if there are, in the beginning of buffer.
    j = 0;
    while (buffer[i])
        buffer[j++] = buffer[i++];
    buffer[j] = '\0';

    printf("buffer : %s\n\n", buffer);

    return (line);
}



int main()
{
//    char *str;
    int fd = open("text.txt", O_RDONLY);
//    char *buffer;
    int i = 0;
    while(i < 12)
    {
        // str = get_next_line(fd);
        // if(!str)
        //     break;
        printf("line : %s\n-------------------------------\n\n", get_next_line(fd));
        // free(str);
        i++;
    }
}
