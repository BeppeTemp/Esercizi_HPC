#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

using namespace std;

int count;

void Tick() {
    #pragma omp atomic
    count = count + 1;
}

int main(int argo, char* argv[]) {
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        Tick();
    }

    printf("%d\n", count);

    return 0;
}