#include "main.h"


Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> ode_system(double t, const Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> &x) {
    MultiInterval<double> k1 = {Interval<double>(0.577)};
    MultiInterval<double> k2 = {Interval<double>(0.410, 0.430)};

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

    std::vector<std::unique_ptr<SolverPlugin>> solver_plugins;
    std::vector<std::unique_ptr<VisualizerPlugin>> visualizer_plugins;

    for (const auto &entry : std::filesystem::directory_iterator("./plugins/"))
    {
        if (entry.path().extension() == ".dll")
        {
            HINSTANCE hGetProcIDDLL = LoadLibraryA(entry.path().string().c_str());

            if (!hGetProcIDDLL)
            {
                std::cout << "Could not load the dynamic library" << std::endl;
                return EXIT_FAILURE;
            }

            GetPluginType getPluginType = (GetPluginType) GetProcAddress(hGetProcIDDLL, "getPluginType");
            if (!getPluginType)
            {
                std::cout << "Could not locate the function 'getPluginType'" << std::endl;
            }

            if (std::string(getPluginType()) == "solver")
            {
                solver_plugins.push_back(std::unique_ptr<SolverPlugin>(new SolverPlugin(hGetProcIDDLL)));
            }
            else if (std::string(getPluginType()) == "visualizer")
            {
                visualizer_plugins.emplace_back(std::unique_ptr<VisualizerPlugin>(new VisualizerPlugin(hGetProcIDDLL)));
            }
        }
    }


    for (auto& solver_plugin : solver_plugins)
    {
        Eigen::Vector<MultiInterval<double>, Eigen::Dynamic> x0(3);
        x0[0] = {Interval<double>(1.0)};
        x0[1] = {Interval<double>(0.0)};
        x0[2] = {Interval<double>(0.0)};

        SolveResult solve_result = solver_plugin->getSolver()->solveODE(
            ode_system,
            x0,
            0.0,
            0.01,
            10.0
        );

        for (auto& visualizer_plugin : visualizer_plugins)
        {
            std::ofstream out_file(visualizer_plugin->getVisualizer()->getFilenameWithExt(std::string("result_") + solver_plugin->pluginName()));
            
            visualizer_plugin->getVisualizer()->writeSolveResultToStream(out_file, solve_result);
            // visualizer_plugin->getVisualizer()->writeSolveResultToStream(std::cout, solve_result);
            
            out_file.close();
        }
    }

    return 0;
}