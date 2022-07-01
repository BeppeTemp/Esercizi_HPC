#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argo, char* argv[]) {
    //! Di default tutte queste sarebbero shared sia per le parallel regione che per i task
    int pr = 100;
    int f_pr = 200;
    int l_pr = 300;

    //! Di default sarebbe shared
    static int s_pr = 400;

    //! Privatizza la variabile s_pr statiche (ma anche globali) senza reinizializzare
    #pragma omp threadprivate(s_pr)

    //! Privatizza la variabile pr reinizializzandola
    //! Privatizza la variabile f_pr come firstprivate senza reinizializzarla
    #pragma omp parallel private(pr) firstprivate(f_pr)
    {
        //! Privatizza la variabile l_pr come lastprivate reinizializzandola e ritornando l'ultimo valore del master (1200/12 = 100)
        //! Aggiunge un bel po di overhead
        #pragma omp for lastprivate(l_pr)
        for (int i = 0; i < 1200; i++)
        {
            l_pr++;
        }

        #pragma omp single
            printf("Hello World... from thread = %d: \t PR %d, F_PR %d, L_PR %d, S_PR %d\n", omp_get_thread_num(), pr, f_pr, l_pr, s_pr);
    }

    printf("\nGoodbye World... from thread = %d: \t PR %d, F_PR %d, L_PR %d, S_PR %d\n", omp_get_thread_num(), pr, f_pr, l_pr, s_pr);

    return 0;
}