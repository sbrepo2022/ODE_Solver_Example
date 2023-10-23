#include "common_methods.h"



class AdamsBashfortMoulton4Solver : public ISolver
{
public:
    virtual ~AdamsBashfortMoulton4Solver()
    {

    }

    SolveResult solveODE(
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*ode_system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),  // return dx/dt vector
        const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,  // start values
        double t0,  // start time
        double h,   // step size
        double T    // end time
    )
    {
        SolveResult solve_result;

        // Начальные 4 шага методом Эйлера
        double t = t0;
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_last_3 = x0;
        solve_result.addStep(t, x_last_3);
        
        t += h;
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_last_2 = x_last_3 + Interval<double>(h) * ode_system(t, x_last_3);
        solve_result.addStep(t, x_last_2);
        
        t += h;
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_last_1 = x_last_2 + Interval<double>(h) * ode_system(t, x_last_2);
        solve_result.addStep(t, x_last_1);
        
        t += h;
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_last_0 = x_last_1 + Interval<double>(h) * ode_system(t, x_last_1);
        solve_result.addStep(t, x_last_0);

        // А затем уже предиктор-корректор
        while (t < T) {
            Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_new_tmp =
                x_last_0 + Interval<double>(h / 24) * (
                Interval<double>(55) * ode_system(t, x_last_0) -
                Interval<double>(59) * ode_system(t - h, x_last_1) +
                Interval<double>(37) * ode_system(t - 2 * h, x_last_2) -
                Interval<double>(9) * ode_system(t - 3 * h, x_last_3));

            Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_new =
                x_last_0 + Interval<double>(h / 24) * (
                Interval<double>(9) * ode_system(t + h, x_new_tmp) +
                Interval<double>(19) * ode_system(t, x_last_0) -
                Interval<double>(5) * ode_system(t - h, x_last_1) +
                ode_system(t - 2 * h, x_last_2));

            x_last_3 = x_last_2;
            x_last_2 = x_last_1;
            x_last_1 = x_last_0;
            x_last_0 = x_new;

            t += h;
            solve_result.addStep(t, x_new);
        }

        return solve_result;
    }
};



extern "C" {

__declspec(dllexport) const char* getPluginType()
{
    return "solver";
}

__declspec(dllexport) const char* getPluginName()
{
    return "Adams_Bashfort_Moulton_4";
}

__declspec(dllexport) ISolver* createSolver()
{
    return new AdamsBashfortMoulton4Solver();
}

__declspec(dllexport) void deleteSolver(ISolver *solver)
{
    delete solver;
}

}
