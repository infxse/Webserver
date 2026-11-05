#ifndef HTTP_H
#define HTTP_H

//  html file, target memory area, max size of area (overflow protection)
void build_http_200_response(const char *html_content, char *response_buffer, int buffer_size);

#endif