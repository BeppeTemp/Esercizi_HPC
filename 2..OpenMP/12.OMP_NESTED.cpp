#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argo, char* argv[]) {
    //! Sembra non funzionare
    omp_set_max_active_levels(2);
    omp_set_dynamic(0);  // make thread number adjustment explicit #pragma omp parallel num_threads(2)
    
    #pragma omp parallel num_threads(4)
    {
        int t1 = omp_get_thread_num();
        #pragma omp parallel num_threads(2)
        {
            int t2 = omp_get_thread_num();
            #pragma omp critical
            { 
                printf("[%d,%d]\n", t1, t2); 
            }
        }
    }

    return 0;
}