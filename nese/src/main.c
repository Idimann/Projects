#include <stdio.h>

#include "buffer.h"

int main(int argc, char** argv) {
    struct buffer buff = buffer_create_empty();
    buffer_setup_file(&buff, "test.txt");
    printf("%lu %s | %s\n", buff.size, buff.callback_addr, buff.text);
    return 0;
}
