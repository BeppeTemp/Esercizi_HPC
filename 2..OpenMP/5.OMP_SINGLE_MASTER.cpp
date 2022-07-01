#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argo, char* argv[]) {

    #pragma omp parallel
    {
        #pragma omp single
        {
            // Questo cambia ogni volta
            printf("Hello World... from single region, my name is = %d\n", omp_get_thread_num());
        }
        //! Qui c'è una barriera
        //! Implementata tramite dei check, in pratica la master è meglio

        #pragma omp master
        {
            // Il master invece è sempre il thread 0
            printf("Hello World... from master regione, my name is = %d\n", omp_get_thread_num());
        }
        //! Qui non c'è una barriera
        //! Implementata con un if(omp_get_thread_num()==0){...} senza barriere
    }

    return 0;
}