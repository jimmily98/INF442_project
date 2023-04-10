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

void Graph::exceldataloadcpp(bool ifprint, std::string filename){
    std::cout << "exceldataloadcpp" << std::endl;
    std::string filepath = "./data/" + filename;
    std::ifstream file(filepath);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::getline(ss, item, ',');
        FromNodeId.push_back(std::stoi(item));
        std::getline(ss, item, ',');
        ToNodeId.push_back(std::stoi(item));
    }
    std::cout<<"exceldataloadcpp end"<<std::endl;
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

void Graph::printEdges() {
    for (int i = 0; i < FromNodeId.size(); ++i) {
        std::cout << FromNodeId[i] << " -> " << ToNodeId[i] << std::endl;
    }
}

void Graph::generateAdjacencyList()//use the relations of edge to generate an adjacency list
{
    int maxNode = 0;
    for (int i = 0; i < FromNodeId.size(); ++i) {
        int fromNode = FromNodeId[i];
        int toNode = ToNodeId[i];
        maxNode = std::max(maxNode, std::max(fromNode, toNode));
    }
    size=maxNode+1;
    vertices.resize(size, 0);
    adjacencyList.resize(size);
    verticesto.resize(size);
    SCC.resize(size);

    for (int i = 0; i < FromNodeId.size(); ++i) {
        int fromNode = FromNodeId[i];
        int toNode = ToNodeId[i];
        adjacencyList[fromNode].push_back(toNode);
        vertices[fromNode] = 1;
        vertices[toNode] = 1;
    }
}

// print a vector
void Graph::printVector(const std::vector<int>& vec) const
    {
        for (int elem : vec) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

// print a 2 dimension vector
void Graph::printNestedVector(const std::vector<std::vector<int>>& nested_vector) const {
        for (const auto& inner_vector : nested_vector) {
            for (int elem : inner_vector) {
                std::cout << elem << ' ';
            }
            std::cout << std::endl;
        }
    }

// DFS on a given point i to find all points that it connects to
void Graph::DFS(int i){
    std::vector<int> havevisited;
    std::vector<int> stack;
    havevisited.resize(size, 0);
    stack.resize(1,i);
    havevisited[i]=1;
    while (stack.size()>0)
    {
        int v=stack.back();
        stack.pop_back();
        for (int neighbor : adjacencyList[v]) {
            if (havevisited[neighbor]==0)
            {
                havevisited[neighbor]=1;
                stack.push_back(neighbor);
            }
        }
    }
    verticesto[i]=havevisited;
}

// compute Stronly connnecte conponents
void Graph::computeSCC(){
    for (int i=0;i<size;i++)
    {
        DFS(i);
    }
    for (int i=0;i<size;i++)
    {
        for (int j=0;j<size;j++)
        {
            if (verticesto[i][j]==1 && verticesto[j][i]==1)
            {
                SCC[i].push_back(j);
            }
        }
    }
}

void Graph::printSCC(){
    std::vector<int> haveprinted;
    haveprinted.resize(size, 0);
    for (int i=0;i<size;i++)
    {
        if (haveprinted[i]==0)
        {
            printVector(SCC[i]);
            for (int neighbor : SCC[i])
            {
                haveprinted[neighbor]=1;
            }
        }
    }
}

double Graph::RandomGene(){
    std::mt19937 generator;
    std::random_device rd;
    std::seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    generator.seed(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double random_value = distribution(generator);
    return random_value;
}

void Graph::ERDirectedGraph(int n, double p, string filename){
    
    assert(n>0 && p>=0 && p<=1);

    // Total number of (eligible) edges: n(n-1)
    FromNodeId.resize(0);
    ToNodeId.resize(0);
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            // assign the edge i -> j with probability p
            if (i!=j && RandomGene()<p)
            {
                FromNodeId.push_back(i);
                ToNodeId.push_back(j);
            }

        }
    }
    // generate the .csv file of FromNodeId and ToNodeId
    std::string filepath = "./data/" + filename;
    ofstream outfile(filepath);
    outfile << "FromNodeId,ToNodeId" << endl;

    for (int i = 0; i < FromNodeId.size(); i++) {
        outfile << FromNodeId[i] << "," << ToNodeId[i] << endl;
    }

    outfile.close();
}

