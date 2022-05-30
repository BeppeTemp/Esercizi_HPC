#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define SIZE 512

/* ------------------------- */
// Results:
/* ------------------------- */
// Size SIZE: ms
// Size SIZE: ms
// Size SIZE: ms
// Size SIZE: ms
/* ------------------------- */

void time_stats(int micro_seconds) {
    cout << "Execution times:" << endl;
    cout << "   * " << micro_seconds << " μs" << endl;
    cout << "   * " << micro_seconds / 1000 << " ms" << endl;
    cout << "   * " << (micro_seconds / 1000) / 1000 << " s" << endl;
}

int main() {
    // Variable declaration

    // Start computation section
    auto start = high_resolution_clock::now();

    // Stop computation section
    auto stop = high_resolution_clock::now();

    time_stats(duration_cast<microseconds>(stop - start).count());

    return 0;
}