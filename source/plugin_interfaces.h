#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <interval_math.h>

using namespace interval_math;

class SolveResult
{
public:
    std::vector<double> t;
    std::vector<Eigen::Vector<MultiInterval<double>, Eigen::Dynamic>> x;

    void addStep(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x)
    {
        this->t.push_back(t);
        this->x.push_back(x);
    }
};


class ISolver
{
public:
    virtual ~ISolver()
    {

    }

    virtual SolveResult solveODE(
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> (*ode_system)(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x),  // return dx/dt vector
        const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x0,  // start values
        double t0,  // start time
        double h,   // step size
        double T    // end time
    ) = 0;
};

class IVisualizer
{
public:
    virtual ~IVisualizer()
    {

    }

    virtual std::string getFilenameWithExt(std::string filename) = 0;
    virtual void writeSolveResultToStream(std::ostream &out, const SolveResult &solve_result) = 0;
};