# get_next_line

## Project Description

The `get_next_line` project is part of the curriculum at 1337 School, which is part of the 42 Network. The goal of this project is to write a function in C that reads and returns a line from a file descriptor. The function should be capable of handling repeated calls, reading one line at a time from the file descriptor.

## Specifications

- The function must be written in C.
- The function must comply with the 42 Norm.
- The function must not cause runtime errors (segmentation fault, bus error, double free, etc.).
- All heap-allocated memory must be properly freed.
- The project must include a Makefile that compiles the source files with the flags `-Wall`, `-Wextra`, and `-Werror`. The Makefile must not perform relinking.
- Bonuses must be implemented in separate files with the suffix `_bonus.{c/h}`.
- The function must not use the `libft` library.
- `lseek()` and global variables are prohibited.
- The project must be submitted to the assigned git repository.

## Required Functions

### Mandatory Part

- **Function Name:** `get_next_line`
- **Prototype:** `char *get_next_line(int fd);`
- **Parameters:** 
  - `fd`: File descriptor to read from.
- **Return Value:**
  - Returns the read line.
  - Returns `NULL` if there is nothing more to read or in case of an error.
- **External Functions:**
  - `read`, `malloc`, `free`
- **Description:**
  - The function must read and return a line from a file descriptor.
  - Repeated calls to `get_next_line` should allow reading the file line by line.
  - The function must work for both file reading and standard input.
  - The returned line should include the `\n` character, except if the end of the file is reached without a `\n`.

### Bonus Part

- Implement `get_next_line` using only one static variable.
- Handle multiple file descriptors simultaneously.
  - E.g., Reading from file descriptors 3, 4, and 5 in separate calls without losing the reading context.

## Files

### Mandatory

- `get_next_line.c`
- `get_next_line.h`
- `get_next_line_utils.c`

### Bonus

- `get_next_line_bonus.c`
- `get_next_line_bonus.h`
- `get_next_line_utils_bonus.c`

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/HaRo97/get_next_line.git
    ```

2. Navigate to the project directory:

    ```sh
    cd get_next_line
    ```

## Usage

To use the `get_next_line` function, include the header file in your C project and link the source files during compilation.

### Include in Your Project

1. Include the header in your source file:

    ```c
    #include "get_next_line.h"
    ```

2. Compile your project with `get_next_line.c` and the utility functions:

    ```sh
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -o my_program my_program.c get_next_line.c get_next_line_utils.c
    ```

### Function Signature

```c
char *get_next_line(int fd);
```

* `fd`: The file descriptor to read from.

### Return Value

* Returns a string containing the next line from the file descriptor.
* Returns `NULL` if there are no more lines to read or if an error occurs.

## Examples

Here is a simple example of how to use `get_next_line` in a program:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

## License

This project is made as part of the 42 School curriculum. Any external use must comply with the rules and licenses of the 42 School.
