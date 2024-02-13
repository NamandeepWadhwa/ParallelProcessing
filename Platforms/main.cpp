// Workshop 1 - Platforms and Optimizations
// w1.cpp
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std::chrono;
#define _RT_INTEL_COMPILER __INTEL_COMPILER

class Version {
public:
    void operator()() const {
        std::cout << "Hello from the ";
#if defined(__GNUC__) 
        std::cout << "GCC compiler: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
#elif defined(__INTEL_LLVM_COMPILER) // for Intel Parallel Studio
        std::cout << "Intel compiler: " << __INTEL_LLVM_COMPILER << std::endl;
#elif defined(_MSC_VER) // for Visual Studio
        std::cout << "Visual Studio compiler: " << _MSC_VER << std::endl;
#else
        std::cout << "Unknown compiler" << std::endl;
#endif
    }
};

// report system time
void reportTime(const char* msg, steady_clock::duration span) {
    auto ms = duration_cast<milliseconds>(span);
    std::cout << msg << " - took - " <<
        ms.count() << " milliseconds" << std::endl;
}

double magnitude(const double* x, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += x[i] * x[i];
    return sqrt(sum);
}

int main(int argc, char* argv[]) {
    Version version;
    version();

    if (argc != 2) {
        std::cerr << argv[0] << ": invalid number of arguments\n";
        std::cerr << "Usage: " << argv[0] << " no_of_elements\n";
        return 1;
    }

    int n = std::atoi(argv[1]); // number of elements in a
    steady_clock::time_point ts, te;

    // allocate memory
    ts = steady_clock::now();
    double* a = new double[n];

    // populate vector a
    for (int i = 0; i < n; i++)
        a[i] = 1.0;

    te = steady_clock::now();
    reportTime(" - allocation and initialization", te - ts);

    // determine magnitude
    ts = steady_clock::now();
    double length = magnitude(a, n);
    te = steady_clock::now();
    reportTime(" - magnitude calculation", te - ts);

    // display result
    std::cout << "Magnitude of a[" << n << "] = " << length << std::endl;

    // deallocate host memory
    delete[] a;

    return 0;
}
