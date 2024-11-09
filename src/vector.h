#include <stdio.h>
#include <stdbool.h>


#ifndef VECTOR_H
#define VECTOR_H

#define CHUNK_SIZE 8
#define DEFAULT_PRINT_PRECISION 2
#define DEFAULT_NEWLINE true

typedef struct {
    double* data;                   // Array holding the data
    unsigned int size;              // Number of non-empty elements
    unsigned int chunk_size;        // Size of new allocated block
    unsigned int num_chunks;        // Number of allocated blocks
    unsigned int num_alloc_elem;    // Number of allocated elements = num_chunks * chunk_size
} Vector;


/** @brief Creates new vector.
 *
 * @return Vector
 */
Vector vector_new();

/** @brief Initializes an empty vector.
 *
 * @param vec Pointer to Vector
 *
 * @return Status code, OK if zero
 */
int vector_init(Vector* vec);

/* Deallocates memory and sets fields (size, num_chunks, num_alloc_elem) to 0. */
void vector_reset(Vector* vec);

/* Allocates new block of memory for storing more data. */
int vector_allocate_new_block(Vector* vec);

/** @brief Appends new value at the end of the vector.
 *
 * @param x Value to append
 * @param vec Pointer to Vector
 *
 * @return Status code, OK if zero
 */
int vector_append(double x, Vector* vec);

/** @brief Removes last element.
 *
 * @param vec Pointer to vector
 *
 * @return Last value or NAN if the vector was already empty
 */
double vector_pop(Vector* vec);

/* Remove a selected element */
double vector_remove(int index, Vector* vec);  // TODO

/* Insert new element at chosen index. */
int vector_insert(double x, int index, Vector* vec);

/* Prints the content of the vector */
void vector_print(Vector* vec, unsigned int num_dec, bool newline);
void vector_print_default(Vector* vec);
void vector_print_details(Vector* vec);



#endif  /* VECTOR_H */
