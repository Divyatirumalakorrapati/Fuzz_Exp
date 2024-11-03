#include <stdio.h>
#include <stdlib.h>
#include "parse_http_request.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Read input file content
    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(length + 1);
    fread(data, 1, length, file);
    data[length] = '\0';

    // Fuzz the parse function
    HttpRequest *req = parse_http_request(data);
    if (req) {
        free(req->method);
        free(req->path);
        free(req->version);
        free(req);
    }

    free(data);
    fclose(file);
    return 0;
}
