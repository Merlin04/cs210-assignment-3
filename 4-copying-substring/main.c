#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../libcompact.h"

char* copy_substr(char* str, size_t start, size_t end) {
    char* copy = malloc(end - start + 1);
    memcpy(copy, str + start, end - start);
    copy[end - start] = '\0';
    return copy;
}

// Testing

MAKE_TEST_FN_STRUCT(1,copy_substr,Pn,char*,char* s;size_t t;size_t e;,(a.s,a.t,a.e),3,{
    {"testing", 1, 6},
    {"Hello, world", 2, 8},
    {"a", 0, 1}
})

int main() {
    t1();
    return 0;
}
