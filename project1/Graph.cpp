#include "Graph.hpp"

using namespace std;

Graph::Graph(){

}

void Graph::exceldataload(bool ifprint) {
    std::cout << "exceldataload" << std::endl;
    Py_Initialize();
    PyObject* sysPath1 = PySys_GetObject("path");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.clear()");
    PyRun_SimpleString("sys.path.append('C:\\\\Users\\\\Hangao Liang\\\\AppData\\\\Local\\\\Programs\\\\Python\\\\Python39\\\\Lib\\\\site-packages')");
    PyRun_SimpleString("sys.path.append('C:\\\\Users\\\\Hangao Liang\\\\OneDrive - Ecole Polytechnique\\\\2AP3\\\\INF442\\\\INF442_project\\\\INF442_project\\\\project1')");
    PyRun_SimpleString("sys.path.append('C:\\\\Users\\\\Hangao Liang\\\\AppData\\\\Local\\\\Programs\\\\Python\\\\Python39\\\\Lib')");
    PyRun_SimpleString("sys.path.append('C:\\\\Users\\\\Hangao Liang\\\\AppData\\\\Local\\\\Programs\\\\Python\\\\Python39\\\\DLLs')");

    // Append the new path to the search path
    
    // const wchar_t* paths = {
    //     L"C:\\Users\\Hangao Liang\\AppData\\Local\\Programs\\Python\\Python39\\python39.zip,\
    //     C:\\Users\\Hangao Liang\\AppData\\Local\\Programs\\Python\\Python39\\Lib,\
    //     C:\\Users\\Hangao Liang\\AppData\\Local\\Programs\\Python\\Python39\\DLLs,\
    //     C:\\Users\\Hangao Liang\\OneDrive - Ecole Polytechnique\\2AP3\\INF442\\INF442_project\\INF442_project,\
    //     C:\\Users\\Hangao Liang\\AppData\\Roaming\\Python\\Python39\\site-packages,\
    //     :\\Users\\Hangao Liang\\OneDrive - Ecole Polytechnique\\2AP3\\INF442\\INF442_project\\INF442_project\\project1"
    // };
    // Py_SetPath(paths);

    // testing code
    // ------------------------------------
    // PyObject* sysModule = PyImport_ImportModule("sys");
    // PyObject* sysPath = PyObject_GetAttrString(sysModule, "path");
    // PyObject* pathList = PySequence_Fast(sysPath, "sys.path not a list");
    // const Py_ssize_t pathListSize = PySequence_Fast_GET_SIZE(pathList);
    // for (Py_ssize_t i = 0; i < pathListSize; ++i) {
    //     PyObject* pathItem = PySequence_Fast_GET_ITEM(pathList, i);
    //     const char* pathStr = PyUnicode_AsUTF8(pathItem);
    //     std::cout << "Python path: " << pathStr << std::endl;
    // }
    // -------------------------------------

    // std::cout << "import dataload.py" << std::endl;
    PyObject* module = PyImport_ImportModule("dataload");
    
    if (!module) {
        PyErr_Print();
        std::cout << "Error importing module." << std::endl;
        return;
    }

    // std::cout << "get the function from the module" << std::endl;
    PyObject* function = PyObject_GetAttrString(module, "load_data");

    // std::cout << "call the function"<< std::endl;
    PyObject* result = PyObject_CallObject(function, NULL);
    if (!result) {
        PyErr_Print();
        std::cout << "Error calling function." << std::endl;
        return;
    }

    // get the list from the tuple returned by the function
    PyObject* list1 = PyTuple_GetItem(result, 0);
    PyObject* list2 = PyTuple_GetItem(result, 1);
    if(!list1){
        std::cout << "Error getting list1" << std::endl;
        return;
    }
    if(!list2){
        std::cout << "Error getting list2" << std::endl;
        return;
    }

    // iterate over the Python list and add each element to the C++ vector
    for (Py_ssize_t i = 0; i < PyList_Size(list1); ++i) {
        PyObject* item = PyList_GetItem(list1, i);
        int value = PyLong_AsLong(item);
        FromNodeId.push_back(value);
    }
    for (Py_ssize_t i = 0; i < PyList_Size(list2); ++i) {
        PyObject* item = PyList_GetItem(list2, i);
        int value = PyLong_AsLong(item);
        ToNodeId.push_back(value);
    }

    Py_Finalize();
    std::cout<<"exceldataload end"<<std::endl;
    
    if(ifprint){
        // Print the vectors
        std::cout << "FromNodeId:";
        for (int i = 0; i < FromNodeId.size(); i++) {
            std::cout << FromNodeId[i] << " ";
        }
        std::cout << "\n ToNodeId:";
        for (int i = 0; i < ToNodeId.size(); i++) {
            std::cout << ToNodeId[i] << " ";
        }
        std::cout << std::endl;
    }
    
}