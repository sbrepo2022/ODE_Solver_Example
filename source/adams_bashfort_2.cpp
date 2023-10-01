#include "common_methods.h"

extern "C" {

__declspec(dllexport) const char* getMethodName()
{
    return "Adams_Bashfort_2";
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
    Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_prev = x;
    double t = t0;

    // Открываем файл для записи
    std::ofstream file(csv_filename);

    writeCSVTitle(file, static_cast<int>(x.size()));

    // Начальный шаг методом Эйлера
    writeValuesToCSV(file, t, x);
    while (t < T) {
        // Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_new
        //     = x + Interval<double>(1.5) * Interval<double>(h) * ode_system(t, x)
        //       - Interval<double>(0.5) * Interval<double>(h) * ode_system(t, x_prev);

        x = x + Interval<double>(h) * ode_system(t, x);
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_new = x_prev + Interval<double>(h / 2.0) * (ode_system(t + h, x) + ode_system(t, x_prev));
        x_prev = x;
        x = x_new;
        t += h;
        writeValuesToCSV(file, t, x);
    }

    // Закрыть файл
    file.close();
}

}
