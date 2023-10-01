#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <interval_math.h>
#include <filesystem>
#include <windows.h>

using namespace interval_math;

typedef const char * (*GetMethodNameMethodType)();
typedef void (*SolveODEMethodType)(
    const std::string &csv_filename,    // output filename
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),  // return dx/dt vector
    const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,  // start values
    double t0,  // start time
    double h,   // step size
    double T    // end time
);

Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> ode_system(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x) {
    MultiInterval<double> k1 = {Interval<double>(0.577)};
    MultiInterval<double> k2 = {Interval<double>(0.01, 1)};

    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> dx(3);
    dx[0] = -k1 * x[0];
    dx[1] = k1 * x[0] - k2 * x[1];
    dx[2] = k2 * x[1];
    return dx;
}

int main(int argc, char **argv) {
    std::filesystem::path currentPath(argv[0]);
    std::filesystem::path directory = currentPath.parent_path();
    std::filesystem::current_path(directory);

    int impl_num = 1;
    for (const auto &entry : std::filesystem::directory_iterator("./")) {
        if (entry.path().extension() == ".dll") {
            HINSTANCE hGetProcIDDLL = LoadLibraryA(entry.path().string().c_str());

            if (!hGetProcIDDLL) {
                std::cout << "Could not load the dynamic library" << std::endl;
                return EXIT_FAILURE;
            }

            SolveODEMethodType solveODE = (SolveODEMethodType) GetProcAddress(hGetProcIDDLL, "solveODE");
            if (!solveODE) {
                std::cout << "Could not locate the function" << std::endl;
                return EXIT_FAILURE;
            }

            GetMethodNameMethodType getMethodName = (GetMethodNameMethodType) GetProcAddress(hGetProcIDDLL, "getMethodName");
            if (!getMethodName) {
                std::cout << "Could not locate the function" << std::endl;
                return EXIT_FAILURE;
            }

            Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x0(3);
            x0[0] = {Interval<double>(1.0)};
            x0[1] = {Interval<double>(0.0)};
            x0[2] = {Interval<double>(0.0)};
            solveODE(
                "result_" + std::string(getMethodName()) + ".csv",
                ode_system,
                x0,
                0.0,
                0.01,
                10.0
            );

            FreeLibrary(hGetProcIDDLL);

            impl_num++;
        }
    }

    return 0;
}