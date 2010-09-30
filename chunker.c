#include <stdio.h>
#include <stdlib.h>

#define EC_EOF_REACHED 1
#define EC_LIMIT_REACHED 0
#define EC_ERROR 2

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No chunk size given!\n");
        return EC_ERROR;
    }
    
    // how big are the chunks?
    long unsigned int chunk_size = strtoul(argv[1], NULL, 10);
    // how much data is (possibly) left to process?
    long unsigned int left = chunk_size;
    
    int returncode = EC_LIMIT_REACHED;
    
    // allocate an input buffer
    void *buffer = malloc( BUFFER_SIZE );
    
    int readBytes = 0;
    while (left > 0) {
        /* how many bytes can we read? We cannot read more than
         * our buffer can handle or our limit allows.
         */
        int toread = BUFFER_SIZE < left ? BUFFER_SIZE : left;
        readBytes = read( 0, buffer, toread );
        if (readBytes == 0) {
            returncode = EC_EOF_REACHED;
            break;
        } else if (readBytes < 0) {
            returncode = EC_LIMIT_REACHED;
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
