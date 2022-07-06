#include <iostream>
#include <CL/sycl.hpp>

#define N 5

using namespace cl::sycl;
/*
    Original code:
    A[0] = B[0];
    A[N] = B[N];
    for(int i=1; i < N-1; i++) {
        A[i] = B[i-1] + B[i] + B[i+1];
    }
*/

int main(){
    int A[5];
    int B[5] = {10, 20, 30, 40, 50};
    A[0] = B[0];
    A[4] = B[4];
    queue queue;
    {
        buffer<int, 1> buf_A{A, range<1>{5}};
        buffer<int, 1> buf_B{B, range<1>{5}};

        queue.submit([&](handler& cgh) {
            accessor write_A {buf_A, cgh, write_only, no_init};
            accessor read_B{buf_B, cgh, read_only, no_init};

            cgh.parallel_for(range<1> (3), [=](id<1> idx) {
                int i = idx;
                i++;
                write_A[i] = read_B[i-1] + read_B[i] + read_B[i+1];
                //write_A[i] = read_B[i];
            });
            
        });
        
    }

    A[0] = B[0];
    A[N-1] = B[N-1];
    
    std::cout << "After sycl execution" << std::endl;
    for(int i=0; i<5; i++)
        std::cout << "A[" << i << "] = " << A[i] << std::endl;


    A[0] = B[0];
    A[N-1] = B[N-1];

    for(int i=1; i < N-1; i++) {
        A[i] = B[i-1] + B[i] + B[i+1];
    }
    std::cout << "After original code" << std::endl;
    for(int i=0; i<5; i++)
        std::cout << "A[" << i << "] = " << A[i] << std::endl;
    

    
}