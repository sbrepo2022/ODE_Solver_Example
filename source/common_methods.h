#include "plugin_interfaces.h"

using namespace interval_math;

extern "C" {

__declspec(dllexport) const char* getPluginType();
__declspec(dllexport) const char* getPluginName();
__declspec(dllexport) ISolver* createSolver();
__declspec(dllexport) void deleteSolver(ISolver *solver);
__declspec(dllexport) IVisualizer* createVisualizer();
__declspec(dllexport) void deleteVisualizer(IVisualizer *visualizer);

}
