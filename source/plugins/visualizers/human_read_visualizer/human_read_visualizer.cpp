#include "common_methods.h"
#include <iomanip>


class HumanReadVisualizer : public IVisualizer
{
public:
    virtual ~HumanReadVisualizer()
    {

    }

    std::string getFilenameWithExt(std::string filename)
    {
        return std::string("human_read_visualize_") + filename + std::string(".txt");
    }

    void writeSolveResultToStream(std::ostream &out, const SolveResult &solve_result)
    {
        int t_col_width = 10;
        int x_col_width = 30;

        size_t size = solve_result.x[0].size();
        // Записываем заголовок
        out << std::left << std::setw(t_col_width) << "t";
        for (size_t i = 0; i < size; i++) {
            std::stringstream ss;
            ss << "x" << i;
            out << std::left << std::setw(x_col_width) << ss.str();
        }
        out << "\n";
        out << std::string(t_col_width + x_col_width * size, '+') << std::endl;

        // Выводим значения
        for (size_t i = 0; i < solve_result.t.size(); i++)
        {
            out << std::left << std::setw(t_col_width) << solve_result.t[i];
            for (int j = 0; j < static_cast<int>(solve_result.x[i].size()); j++) {
                out << std::left << std::setw(x_col_width) << solve_result.x[i][j];
            }
            out << "\n";
            out << std::string(t_col_width + x_col_width * size, '-') << std::endl;
        }
    }
};



extern "C" {

__declspec(dllexport) const char* getPluginType()
{
    return "visualizer";
}

__declspec(dllexport) const char* getPluginName()
{
    return "human_read_visualizer";
}

__declspec(dllexport) IVisualizer* createVisualizer()
{
    return new HumanReadVisualizer();
}

__declspec(dllexport) void deleteVisualizer(IVisualizer *visualizer)
{
    delete visualizer;
}

}