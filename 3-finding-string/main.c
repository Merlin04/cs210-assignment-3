#include <stdio.h>
#include "../libcompact.h"

// Write a function that given two input strings, returns a pointer to the
// first instance of the second string that occurs in the first string. Neither input string may be NULL.
// The second string may or may not occur in the first string. If it does not, you should return a pointer
// to the terminal character of the first string. You are not allowed to use functions in the ¡string¿ library.
// You are allowed to add additional arguments to your function as necessary.

char* find_str(char* a, char* b) {
    for(char* s = a; *s; s++) {
        char* cmp = s;
        for(; b[cmp-s] && *cmp == b[cmp-s]; cmp++);
        if(!(b[cmp-s])) {
            return s;
        }
    }
    return a;
}

// Testing
MAKE_TEST_FN_STRUCT(1,find_str,Pn,char*,char* a;char* b;,(a.a,a.b),5,{
    {"Hello, world!", "llo"},
    {"Testing", "qqqqqq"},
    {"", ""},
    { "Glubglogabgalab", "gal"}
})

int main() {
    t1();
    return 0;
}
