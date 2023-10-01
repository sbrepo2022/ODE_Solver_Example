#include "common_methods.h"

Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> rungeKutta4(
    const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*ode_system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),
    double t,
    double h
);

extern "C" {

__declspec(dllexport) const char* getMethodName()
{
    return "Runge_Kutta_4";
}

__declspec(dllexport) void solveODE(
    const std::string &csv_filename,    // output filename
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*ode_system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),  // return dx/dt vector
    const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,  // start values
    double t0,  // start time
    double h,   // step size
    double T    // end time
)
{
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x = x0;
    double t = t0;

    // Открываем файл для записи
    std::ofstream file(csv_filename);

    writeCSVTitle(file, static_cast<int>(x.size()));
    writeValuesToCSV(file, t, x);
    while (t <= T) {
        x = rungeKutta4(x, ode_system, t, h);
        t += h;
        writeValuesToCSV(file, t, x);
    }

    // Закрыть файл
    file.close();
}

}

// Метод Рунге-Кутты 4-го порядка
Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> rungeKutta4(
    const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*ode_system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),
    double t,
    double h
) {
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> k1 = ode_system(t, x0);
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> k2 = ode_system(t, x0 + Interval<double>(0.5) * Interval<double>(h) * k1);
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> k3 = ode_system(t, x0 + Interval<double>(0.5) * Interval<double>(h) * k2);
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> k4 = ode_system(t, x0 + Interval<double>(h) * k3);

    return x0 + Interval<double>(h / 6.0) * (k1 + Interval<double>(2.0) * k2 + Interval<double>(2.0) * k3 + k4);
}
