#include <stdio.h>
#include <fcntl.h>      // For open() flags
#include <unistd.h>     // For read(), write(), close()
#include <stdlib.h>     // For exit()

int main() {
    int src_fd, dest_fd;       // File descriptors
    char buffer[1024];         // Buffer to store file data
    ssize_t bytes_read, bytes_written;

    src_fd = open("result.txt", O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening result.txt");
        exit(1);
    }

    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error creating copyresult.txt");
        close(src_fd);
        exit(1);
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to copyresult.txt");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read < 0) {
        perror("Error reading result.txt");
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully from result.txt to copyresult.txt\n");
    return 0;
}
