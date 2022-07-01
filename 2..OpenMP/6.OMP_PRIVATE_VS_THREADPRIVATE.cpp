#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argo, char* argv[]) {
    // Questa variabile è shared
    int x = 5;
    static int y = 10;

    // privatizza variabili statiche
    #pragma omp threadprivate(y)

    #pragma omp parallel private(x)
    {
        // La variabile diventa private e viene settata a 0

        if (omp_get_thread_num() == 0) {
            x++;
            y++;
        }

        printf("Hello World... from thread = %d, vr_one %d, vr_two %d\n", omp_get_thread_num(), x, y);

    }

    return 0;
}