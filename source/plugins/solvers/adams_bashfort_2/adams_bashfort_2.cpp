#include "common_methods.h"



class AdamsBashfort2Solver : public ISolver
{
public:
    virtual ~AdamsBashfort2Solver()
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

        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x = x0;
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_prev = x;
        double t = t0;

        // Начальный шаг методом Эйлера
        solve_result.addStep(t, x);
        while (t < T) {
            x = x + Interval<double>(h) * ode_system(t, x);
            Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x_new = x_prev + Interval<double>(h / 2.0) * (ode_system(t + h, x) + ode_system(t, x_prev));
            x_prev = x;
            x = x_new;
            t += h;
            solve_result.addStep(t, x);
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
    return "Adams_Bashfort_2";
}

__declspec(dllexport) ISolver* createSolver()
{
    return new AdamsBashfort2Solver();
}

__declspec(dllexport) void deleteSolver(ISolver *solver)
{
    delete solver;
}

}
