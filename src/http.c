#include "http.h"
#include <stdio.h>
#include <string.h>

void build_http_200_response(const char *html_content, char *response_buffer, int buffer_size)
{
    int content_len = strlen(html_content);

    // http: every line must end with "\r\n" (CRLF). 
    // "\r\n\r\n" separates header from body.
    snprintf(
        response_buffer,
        buffer_size,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n" //header ends and body starts.
        "%s",
        content_len,
        html_content
    );
}