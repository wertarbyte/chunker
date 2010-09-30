#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No chunk size given!\n");
        return 2;
    }
    
    // how big are the chunks?
    long unsigned int chunk_size = strtoul(argv[1], NULL, 10);
    // how much data is (possibly) left to process?
    long unsigned int left = chunk_size;
    
    int returncode = 0;

    int buffer_size = 8;
    void *buffer = malloc( buffer_size );
    
    int readBytes = 0;
    while (left > 0) {
        int toread = buffer_size < left ? buffer_size : left;
        // fprintf(stderr, "%d bytes left\n", left);
        readBytes = read( 0, buffer, toread );
        // fprintf(stderr, "Read %d bytes\n", readBytes);
        if (readBytes == 0) {
            returncode = 1;
            break;
        } else if (readBytes < 0) {
            returncode = 2;
            fprintf(stderr, "Read error\n");
            break;
        } else {
            write(1, buffer, readBytes );
            left -= readBytes;
        }
    }
    free(buffer);
    return returncode;
}
