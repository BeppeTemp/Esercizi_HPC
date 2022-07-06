#include <iostream>
#include <sycl/sycl.hpp>
#include <vector>

using namespace std;
using namespace sycl;

constexpr int size = 131072;  // 2^17

int main(int argc, char** argv) {
    // Create a vector with size elements and initialize them to 1
    vector<float> dA(size, 1);
    vector<float> dB(size, 1);
    vector<float> dO(size);

    try {

        queue gpuQueue{gpu_selector{}};

        buffer<float, 1> bufA(dA.data(), range<1>(dA.size()));
        buffer<float, 1> bufB(dB.data(), range<1>(dB.size()));
        buffer<float, 1> bufO(dO.data(), range<1>(dO.size()));

        gpuQueue.submit([&](handler& cgh) {
            accessor inA{bufA, cgh};
            accessor inB{bufB, cgh};
            accessor out{bufO, cgh};

            cgh.parallel_for(range<1>(size), [=](id<1> i) { out[i] = inA[i] + inB[i]; });
        });

        gpuQueue.wait_and_throw();

    } catch (std::exception& e) {
        throw e;
    }

    for (auto& e : dO)
        assert(e == 2);
        
    std::cout << "TEST PASSED!\n";
    return 0;
}