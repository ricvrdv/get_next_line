# GET_NEXT_LINE

### [MILESTONE 1]
### SUMMARY
This repository contains an implementation of the `get_next_line` function, which reads a file descriptor line by line. It is designed to handle files and standard input efficiently using a buffer to store intermediate data.

Key features include:
- Reading lines one by one from files or standard input.
- Handling different buffer sizes using the `BUFFER_SIZE` macro.
- Returning the line including the trailing newline character (if present).
- Storing unread characters for subsequent calls using a **static variable**.

This project adheres to strict coding standards and disallows the use of global variables or certain library functions (e.g., `lseek`).

The repository is structured as follows:

- **`get_next_line.c`**:
  Implements the main logic to read and process lines from the file descriptor.

- **`get_next_line_utils.c`**:
    Contains helper functions for string manipulation (`ft_strjoin`, `ft_strchr`, etc.).

- **`get_next_line.h`**:
  Header file defining function prototypes and including necessary libraries.

Compile the project using the following command:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<value> get_next_line.c get_next_line_utils.c -o get_next_line
```
