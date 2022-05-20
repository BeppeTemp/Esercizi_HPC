#include <omp.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    const int size = 512;

    double A[size];
    double B[size];
    double C[size];

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 3.0;
    }

    double t_init = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Th.num: " << omp_get_num_threads() << endl;
            fflush(stdout);
        }
        #pragma omp for
        for (int i = 0; i < size; i++) {
            A[i] = B[i] + C[i];
        }
    }

    // print results
    for (int i = 0; i < size; i++) {
        cout << C[i] << " ";
    }
    
    cout << "Time:" << omp_get_wtime() - t_init << endl;
    return 0;
}