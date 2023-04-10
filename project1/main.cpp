#include <stdio.h>
#include <vector>
#include <iostream>
#include <time.h>
#include "Graph.hpp"

using namespace std;

int main()
{
    clock_t start_time, end_time;
    double total_time;
    
    start_time = clock(); 
    Graph G;
    std::string filename = "test.csv";
    int n = 15;
    double p = 0.15;

    // Generate a random digraph
    G.ERDirectedGraph(n,p,filename);
    try
    {
        G.exceldataloadcpp(false, filename);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: ";
        std::cerr << e.what() << '\n';
    }
    G.generateAdjacencyList();
    // Print the graph edges
    // std::cout << "Edges:" << std::endl;
    // G.printEdges();

    G.computeSCC();
    G.printSCC();

    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Total time: " << total_time << "s" << std::endl;
    std::cout << "Press any key to exit...";
    getchar(); // waits for user to press any key
    return 0;
}
