#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

using namespace std;

int main(int argo, char* argv[]) {
    //! Master, assegnato nello stesso socket del padre
    //! Close, assegnato vicino allo stesso socket del padre
    //! Spread, assegnato in modo uniforme nei socket

    // Prima li spargiamo
    #pragma omp parallel proc_bind(spread) num_threads(4)
    for (int i = 0; i < SIZE; i++) {
        // Poi ognuno di quelli sparsi ne crea qualcuno vicino
        #pragma omp parallel proc_bind(close) num_threads(4)
        for (int j = 0; j < SIZE; j++) {
            /* do some work */
        }
    }

    return 0;
}