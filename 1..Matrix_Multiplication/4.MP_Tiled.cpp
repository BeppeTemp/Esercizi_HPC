#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define SIZE 2046
#define TILE 32

/* ------------------------- */
// Results:
/* ------------------------- */
// Size 256:    2.50 ms
// Size 512:    16.24 ms
// Size 1024:   74.86 ms
// Size 2048:   562.42 ms
/* ------------------------- */

void time_stats(float micro_seconds) {
    cout << "Execution times:" << endl;
    printf("    * %.0f μs \n", micro_seconds);
    printf("    * %.2f ms \n", micro_seconds / 1000);
    printf("    * %.2f s \n", micro_seconds / 1000 / 1000);
    printf("    * %.0f minutes and %d seconds\n",
           ((micro_seconds / 1000) / 1000) / 60,
           (int)((micro_seconds / 1000) / 1000) % 60);
}

void generate(int* mat) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        mat[i] = rand() % 10;
    }
}

void printMat(int* mat) {
    printf("\n");
    for (int i = 0; i < (SIZE * SIZE); i++) {
        printf("|");
        printf("%d", mat[i]);
        if (((i + 1) % (SIZE) == 0) && (i != 0))
            printf("|\n");
        if ((SIZE * SIZE) == 1)
            printf("|\n");
        if (SIZE == 1 && ((i == 0)))
            printf("|\n");
    }
    printf("\n");
}

int main() {
    int* mat_one = new int[SIZE * SIZE]();
    int* mat_two = new int[SIZE * SIZE]();

    generate(mat_one);
    generate(mat_two);

    if (SIZE <= 10) {
        cout << "Fist matrix: \n";
        printMat(mat_one);

        cout << "Second matrix: \n";
        printMat(mat_two);
    }

    int* mat_result = new int[SIZE * SIZE]();

    auto start = high_resolution_clock::now();

    #pragma omp parallel for
    for (int ih = 0; ih < SIZE; ih += TILE)
        #pragma omp parallel for
        for (int jh = 0; jh < SIZE; jh += TILE)
            for (int kh = 0; kh < SIZE; kh += TILE)
                for (int il = 0; il < TILE; il++)
                    for (int kl = 0; kl < TILE; kl++)
                        for (int jl = 0; jl < TILE; jl++)
                            mat_result[(ih + il) * TILE + (jh + jl)] +=
                                mat_one[(ih + il) * TILE + (kh + kl)] * mat_two[(kh + kl) * TILE + (jh + jl)];

    auto stop = high_resolution_clock::now();

    if (SIZE <= 10) {
        cout << "Result matrix: \n";
        printMat(mat_result);
    }

    time_stats(duration_cast<microseconds>(stop - start).count());

    return 0;
}