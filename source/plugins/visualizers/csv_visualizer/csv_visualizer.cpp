#include "common_methods.h"


class CsvVisualizer : public IVisualizer
{
public:
    virtual ~CsvVisualizer()
    {

    }

    std::string getFilenameWithExt(std::string filename)
    {
        return std::string("csv_visualize_") + filename + std::string(".csv");
    }

    void writeSolveResultToStream(std::ostream &out, const SolveResult &solve_result)
    {
        size_t size = solve_result.x[0].size();
        // Записываем заголовок
        out << "t,";
        for (size_t i = 0; i < size; i++) {
            out << "x" << i;
            if (i != size - 1) out << ",";
        }
        out << "\n";

        // Выводим значения
        for (size_t i = 0; i < solve_result.t.size(); i++)
        {
            out << solve_result.t[i] << ",";
            for (int j = 0; j < static_cast<int>(solve_result.x[i].size()); j++) {
                out << solve_result.x[i][j];
                if (j != solve_result.x[i].size() - 1) out << ",";
            }
            out << "\n";
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
    return "csv_visualizer";
}

__declspec(dllexport) IVisualizer* createVisualizer()
{
    return new CsvVisualizer();
}

__declspec(dllexport) void deleteVisualizer(IVisualizer *visualizer)
{
    delete visualizer;
}

}