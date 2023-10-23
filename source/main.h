#include <interval_math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <memory>
#include <windows.h>
#include "plugin_interfaces.h"

using namespace interval_math;

typedef const char* (*GetPluginType)();
typedef const char* (*GetPluginName)();
typedef ISolver* (*CreateSolver)();
typedef void (*DeleteSolver)(ISolver*);
typedef IVisualizer* (*CreateVisualizer)();
typedef void (*DeleteVisualizer)(IVisualizer*);


class PluginMethods
{
protected:
    HINSTANCE hGetProcIDDLL;
    GetPluginType getPluginType;
    GetPluginName getPluginName;

public:
    PluginMethods(HINSTANCE hGetProcIDDLL) :
        hGetProcIDDLL(hGetProcIDDLL),
        getPluginType(nullptr),
        getPluginName(nullptr)
    {
        this->getPluginName = (GetPluginName) GetProcAddress(hGetProcIDDLL, "getPluginName");
        if (!getPluginName) {
            std::cout << "Could not locate the function 'getPluginName'" << std::endl;
        }

        this->getPluginType = (GetPluginType) GetProcAddress(hGetProcIDDLL, "getPluginType");
        if (!getPluginType) {
            std::cout << "Could not locate the function 'getPluginType'" << std::endl;
        }
    }

    virtual ~PluginMethods()
    {
        FreeLibrary(hGetProcIDDLL);
    }

    std::string pluginType()
    {
        return std::string(getPluginType());
    }

    std::string pluginName()
    {
        return std::string(getPluginName());
    }
};



class SolverPlugin : public PluginMethods
{
protected:
    ISolver *solver;
    CreateSolver createSolver;
    DeleteSolver deleteSolver;

public:
    SolverPlugin(HINSTANCE hGetProcIDDLL) :
        PluginMethods(hGetProcIDDLL),
        solver(nullptr),
        createSolver(nullptr),
        deleteSolver(nullptr) 
    {
        this->createSolver = (CreateSolver) GetProcAddress(hGetProcIDDLL, "createSolver");
        if (!createSolver) {
            std::cout << "Could not locate the function 'createSolver'" << std::endl;
        }

        this->deleteSolver = (DeleteSolver) GetProcAddress(hGetProcIDDLL, "deleteSolver");
        if (!deleteSolver) {
            std::cout << "Could not locate the function 'deleteSolver'" << std::endl;
        }

        if (createSolver)
            this->solver = this->createSolver();
    }

    virtual ~SolverPlugin()
    {
        if (deleteSolver)
            deleteSolver(solver);
    }

    ISolver* getSolver()
    {
        return solver;
    }
};



class VisualizerPlugin : public PluginMethods
{
private:
    IVisualizer *visualizer;
    CreateVisualizer createVisualizer;
    DeleteVisualizer deleteVisualizer;

public:
    VisualizerPlugin(HINSTANCE hGetProcIDDLL) :
        PluginMethods(hGetProcIDDLL),
        visualizer(nullptr),
        createVisualizer(nullptr),
        deleteVisualizer(nullptr) 
    {
        this->createVisualizer = (CreateVisualizer) GetProcAddress(hGetProcIDDLL, "createVisualizer");
        if (!createVisualizer) {
            std::cout << "Could not locate the function 'createVisualizer'" << std::endl;
        }

        this->deleteVisualizer = (DeleteVisualizer) GetProcAddress(hGetProcIDDLL, "deleteVisualizer");
        if (!deleteVisualizer) {
            std::cout << "Could not locate the function 'deleteVisualizer'" << std::endl;
        }

        if (createVisualizer)
            this->visualizer = this->createVisualizer();
    }

    virtual ~VisualizerPlugin()
    {
        if (deleteVisualizer)
            deleteVisualizer(visualizer);
    }

    IVisualizer* getVisualizer()
    {
        return visualizer;
    }
};
