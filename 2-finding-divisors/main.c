#include <stdio.h>
#include <stdlib.h>
#include "../libcompact.h"[]

// Write a function that given an array of positive integers, returns all of
// the pairs of integers such that the first evenly divides the second. The output should be formatted as
// two arrays, where the element in position i in the first array evenly divides the element in position i in
// the second array. If there are no such integers, both arrays should contain 0. A number may show up in
// multiple entries, but there should be no duplicate entries. Assume that the input contains no duplicates.
// The input array may not be NULL. You are allowed to add additional arguments to your function as
// necessary.

typedef struct {
    int *first;
    int *second;
    size_t len;
} Pair;

Pair* find_divisors(int* arr, size_t len) {
    int* first = malloc(sizeof *first * len * len);
    int* second = malloc(sizeof *second * len * len);
    size_t out_len = 0;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            if (arr[j] % arr[i] == 0) {
                first[out_len] = arr[i];
                second[out_len] = arr[j];
                out_len++;
            }
        }
    }

    if(out_len == 0) {
        first[0] = 0;
        second[0] = 0;
        out_len++;
    }

    // resize arr to match out_len so we're not wasting memory
    first = realloc(first, (sizeof *first) * out_len);
    second = realloc(second, (sizeof *second) * out_len);

    return &(Pair){
        .first = first,
        .second = second,
        .len = out_len
    };
}

// Testing
#define Pp(p) {Pad(p->first, p->len);Pad(p->second, p->len);Pd(p->len);P("\n");}
MAKE_TEST_FN_STRUCT(1,find_divisors,Pp,Pair*,int* arr;size_t len;,(a.arr,a.len),2,{
    {(int[]){1, 2, 3, 4, 5, 10, 11, 12, 13, 14}, 10},
    {(int[]){}, 0}
})

int main() {
    t1();
    return 0;
}
