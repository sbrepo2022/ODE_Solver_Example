#include <Eigen/Dense>
#include <fstream>
#include <string>
#include <interval_math.h>

using namespace interval_math;

extern "C" {

__declspec(dllexport) const char* getMethodName();

__declspec(dllexport) void solveODE(
    const std::string &csv_filename,    // output filename
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*ode_system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),  // return dx/dt vector
    const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,  // start values
    double t0,  // start time
    double h,   // step size
    double T    // end time
);

}

void writeCSVTitle(std::ofstream &file, int size)
{
    // Записываем заголовок
    file << "t,";
    for (int i = 0; i < size; i++) {
        file << "x" << i;
        if (i != size - 1) file << ",";
    }
    file << "\n";
}

void writeValuesToCSV(std::ofstream &file, double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x)
{
    // Выводим значения
    file << t << ",";
    for (int i = 0; i < static_cast<int>(x.size()); i++) {
        file << x[i];
        if (i != x.size() - 1) file << ",";
    }
    file << "\n";
}