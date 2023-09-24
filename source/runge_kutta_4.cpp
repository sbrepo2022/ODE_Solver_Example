#include "common_methods.h"

Eigen::VectorXd rungeKutta4(
    const Eigen::VectorXd &x0,
    Eigen::VectorXd (*ode_system)(double t, const Eigen::VectorXd &x),
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
    Eigen::VectorXd (*ode_system)(double t, const Eigen::VectorXd &x),  // return dx/dt vector
    const Eigen::VectorXd &x0,  // start values
    double t0,  // start time
    double h,   // step size
    double T    // end time
)
{
    Eigen::VectorXd x = x0;
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
Eigen::VectorXd rungeKutta4(
    const Eigen::VectorXd &x0,
    Eigen::VectorXd (*ode_system)(double t, const Eigen::VectorXd &x),
    double t,
    double h
) {
    Eigen::VectorXd k1 = ode_system(t, x0);
    Eigen::VectorXd k2 = ode_system(t, x0 + 0.5 * h * k1);
    Eigen::VectorXd k3 = ode_system(t, x0 + 0.5 * h * k2);
    Eigen::VectorXd k4 = ode_system(t, x0 + h * k3);

    return x0 + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}
