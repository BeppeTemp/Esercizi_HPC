#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argo, char* argv[]) {
    int x = 5;

    #pragma omp parallel private(x)
    {
    //! La variabile diventa private e viene settata a 0

    if (omp_get_thread_num() == 0) {
        x++;
    }
    
    printf("Hello World... from thread = %d, vr %d\n", omp_get_thread_num(), x);
    if (omp_get_thread_num() == 0)
        printf("Numero di thread: %d \n", omp_get_max_threads());
    }

    return 0;
}