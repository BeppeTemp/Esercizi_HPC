#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define SIZE 2048

/* Tests:
    128: 12 ms
    256: 55 ms
    512: 535 ms
    1024: 4642 ms
    2048: 108816 ms
*/

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

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            for (int k = 0; k < SIZE; ++k) {
                mat_result[i * SIZE + j] +=
                    mat_one[i * SIZE + k] * mat_two[k * SIZE + j];
            }

    auto stop = high_resolution_clock::now();

    if (SIZE <= 10) {
        cout << "Result matrix: \n";
        printMat(mat_result);
    }

    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: "<< duration.count() / 1000 << " ms" << endl;

    return 0;
}