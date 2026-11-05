#include "file.h"
#include "log.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


char* read_html_file(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    if (NULL == file) {
        perror("Error occurred while trying to load an html document.");

        return NULL;
    }

    //get file size by jumping to EOF.
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (NULL == buffer) {
        perror("Error while trying to load html document (ALLOC_BUFFER).");
        fclose(file);

        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0'; // Wichtig: String in C manuell terminieren!
    DEBUG_LOG("Loaded html doc into memory successfully!");

    fclose(file);

    return buffer;
}