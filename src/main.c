#include <stdio.h>
#include <stdbool.h>
#include "vector.h"


double x;


int main() {
    printf("=========================================\n");
    printf("Create new vector...\n");
    Vector vec = vector_new();

    printf("=========================================\n");
    printf("Fill it with 10 values...\n");
    for (int i=0; i < 10; i++) {
        vector_append(i, &vec);
        vector_print_details(&vec);
        printf("\n");
    }

    printf("=========================================\n");
    printf("Pop last value...\n");
    x = vector_pop(&vec);
    printf("x = %.2f\n", x);
    vector_print_default(&vec);

    printf("=========================================\n");
    printf("Insert a value 99 at index 1...\n");
    vector_insert(99, 1, &vec);
    vector_print_default(&vec);

    printf("=========================================\n");
    printf("Remove some values...\n");
    x = vector_remove(1, &vec);
    printf("x = %.2f\n", x);
    x = vector_remove(0, &vec);
    printf("x = %.2f\n", x);
    x = vector_remove(5, &vec);
    printf("x = %.2f\n", x);
    vector_print_details(&vec);

    printf("=========================================\n");
    printf("Print in all possible ways...\n");
    vector_print(&vec, 4, true);
    vector_print_default(&vec);
    vector_print_details(&vec);


    return 0;
}
