#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "return_codes.h"


Vector vector_new() {
    Vector vec = {
        .data = NULL,
        .size = 0,
        .chunk_size = CHUNK_SIZE,
        .num_chunks = 0,
        .num_alloc_elem = 0,
    };
    vector_init(&vec);

    return vec;
}

int vector_init(Vector* vec) {

    if (vec->size > 0) {
        vector_reset(vec);
    }

    vec->chunk_size = CHUNK_SIZE;
    vec->data = (double*) malloc(sizeof(double) * vec->chunk_size);

    if (vec->data == NULL) {
        fprintf(stderr, "Memory allocation for vector failed!\n");
        return ERR;
    }

    vec->size = 0;
    vec->num_chunks = 1;
    vec->num_alloc_elem = vec->chunk_size;

    return OK;
}

void vector_reset(Vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->chunk_size = CHUNK_SIZE;
    vec->num_chunks = 0;
    vec->num_alloc_elem = 0;
}

int vector_allocate_new_block(Vector* vec) {

    vec->num_chunks++;
    size_t new_size = sizeof(double) * vec->chunk_size * vec->num_chunks;
    double* new_data = (double*) realloc(vec->data, new_size);

    if (new_data == NULL) {
        fprintf(stderr, "Memory allocation for vector failed!\n");
        free(vec->data);
        return ERR;
    }

    vec->data = new_data;
    vec->num_alloc_elem += vec->chunk_size;

    return OK;
}

int vector_append(double x, Vector* vec) {

    // Need to allocate more memory if needed
    if (vec->size + 1 > vec->num_alloc_elem) {
        vector_allocate_new_block(vec);
    }

    // Append new value
    vec->data[vec->size] = x;
    vec->size++;

    return OK;
}

double vector_pop(Vector* vec) {
    if (vec->size > 0) {
        vec->size--;
        return vec->data[vec->size];
    }
    else {
        fprintf(stderr, "Cannot pop from an empty vector\n");
        return NAN;
    }
}

double vector_remove(int index, Vector* vec) {
    if ((index < 0) || (index >= vec->size)) {
        fprintf(stderr, "Wrong index (%d)\n", index);
        return NAN;
    }
    // Get the value at index
    double val = vec->data[index];

    // Move subsequent elements 1 left
    for (int i=index; i < vec->size - 1; i++) {
        vec->data[i] = vec->data[i+1];
    }
    vec->size--;

    return val;
}

int vector_insert(double x, int index, Vector* vec) {
    if (index < 0) {
        fprintf(stderr, "Negative index is not supported yet!\n");
        return ERR;
    }

    // Compare index to current vector size and allocate more memory if needed
    if (index > vec->size) {
        fprintf(stderr, "Index (%d) is larger than the size of the vector!", index);
        return ERR;
    }

    if (index >= vec->num_alloc_elem) {
        vector_allocate_new_block(vec);
    }

    // If index is at the end, just append the value and return
    if (index == vec->size) {
        return vector_append(x, vec);
    }

    // Copy current element at that index
    double aux = vec->data[index];

    // Move all subsequent elements by 1
    for (int i=vec->size; i > index; i--) {
        vec->data[i] = vec->data[i-1];
    }

    // Insert x at index
    vec->data[index] = x;
    vec->size++;

    return OK;
}

void vector_print(Vector* vec, unsigned int num_dec, bool newline) {

    // Get the format specifier with precision (num_dec)
    const unsigned int max_fmt_len = 20;
    char fmt[max_fmt_len];
    snprintf(fmt, sizeof(fmt), "%%.%df", num_dec);

    // Print the values
    printf("[");
    for (int i=0; i < vec->size; i++) {
        printf(fmt, vec->data[i]);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf("]");
    if (newline) {
        printf("\n");
    }
}

void vector_print_default(Vector* vec) {
    vector_print(vec, DEFAULT_PRINT_PRECISION, DEFAULT_NEWLINE);
}

void vector_print_details(Vector* vec) {
    printf("Vector =\n");
    vector_print(vec, DEFAULT_PRINT_PRECISION, true);
    printf("{\n");
    printf("    vec.size = %d\n", vec->size);
    printf("    vec.num_chunks = %d\n", vec->num_chunks);
    printf("    vec.num_alloc_elem = %d\n", vec->num_alloc_elem);
    printf("}\n");
}
