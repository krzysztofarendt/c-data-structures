#include <stdio.h>
#include <stdbool.h>
#include "vector.h"


int main() {
    printf("Start\n");
    Vector vec = vector_new();

    for (int i=0; i < 10; i++) {
        vector_append(i, &vec);
        vector_print_details(&vec);
        printf("\n");
    }

    double x = vector_pop(&vec);
    printf("x = %.2f\n", x);
    vector_print_details(&vec);

    printf("============\n");
    vector_print(&vec, 4, true);
    vector_print_default(&vec);

    printf("============\n");
    vector_insert(99, 1, &vec);
    vector_print_default(&vec);

    return 0;
}
