#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "return_codes.h"


// Test wrapper
void test(void (*test_function)(), char* name) {
    printf("Testing: %s\n", name);
    test_function();
}


// Tests //////////////////////////////////////////////////////////////////////
void test_vector_new() {
    Vector vec = vector_new();
    assert(vec.size == 0);
    assert(vec.data != NULL);
}


void test_vector_append() {
    Vector vec = vector_new();
    for (int i=0; i<100; i++) {
        assert(vec.size == i);
        vector_append((double) i, &vec);
        assert(vec.data[i] == i);
    }
    assert(vec.size == 100);
}


void test_vector_insert() {
    Vector vec = vector_new();
    for (int i=0; i < 5; i++) {
        vector_append(i, &vec);
    }

    vector_insert(-1, 0, &vec);
    assert(vec.size == 6);
    assert(vec.data[0] == -1);
    assert(vec.data[1] == 0);
    // ... skipped middle elements
    assert(vec.data[5] == 4);
}


int main() {
    printf("========== TESTS STARTED ==========\n");
    test(test_vector_new, "vector_new()");
    test(test_vector_append, "vector_append()");
    test(test_vector_insert, "vector_insert()");

    printf("======== ALL TESTS PASSED! ========\n");
    return OK;
}
