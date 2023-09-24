#include "common_methods.h"

extern "C" {

__declspec(dllexport) const char* getMethodName()
{
    return "Adams_Bashfort_2";
}

__declspec(dllexport) void solveODE(
    const std::string &csv_filename,    // output filename
    Eigen::VectorXd (*ode_system)(double t, const Eigen::VectorXd &x),  // return dx/dt vector
    const Eigen::VectorXd &x0,  // start values
    double t0,  // start time
    double h,   // step size
    double T    // end time
)
{
    Eigen::VectorXd x = x0;
    Eigen::VectorXd x_prev = x;
    double t = t0;

    // Открываем файл для записи
    std::ofstream file(csv_filename);

    writeCSVTitle(file, static_cast<int>(x.size()));

    // Начальный шаг методом Эйлера
    x = x + h * ode_system(t, x);
    writeValuesToCSV(file, t, x);
    while (t < T) {
        Eigen::Vector3d x_new = x + 1.5 * h * ode_system(t, x) - 0.5 * h * ode_system(t, x_prev);
        x_prev = x;
        x = x_new;
        t += h;
        writeValuesToCSV(file, t, x);
    }

    // Закрыть файл
    file.close();
}

}
