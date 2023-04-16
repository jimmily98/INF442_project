#include <stdio.h>
#include <vector>
#include <iostream>
#include <time.h>
#include "dbscan.hpp"

using namespace std;

int main()
{
    clock_t start_time, end_time;
    double total_time;
    
    start_time = clock(); 
    Graph G;
    DBSCAN D(2, 3);
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

    //tested on (2, 3), (3, 4), (4, 4), (4, 5), (5, 5), (6, 4), (6, 5), (6, 6), (7, 5), (8, 7)
    std::vector<std::vector<double>> sampleDistances = {
        {0, sqrt(2), sqrt(5), sqrt(8), sqrt(13), sqrt(17), sqrt(20),5,sqrt(29),sqrt(52)},
        {sqrt(2), 0, 1, sqrt(2), sqrt(5), 3, sqrt(10),sqrt(13),sqrt(17),sqrt(34)},
        {sqrt(5), 1, 0, 1, sqrt(2), 2, sqrt(5),sqrt(8),sqrt(10),5},
        {sqrt(8), sqrt(2), 1, 0, 1, sqrt(5),2,sqrt(5),3,sqrt(20)},
        {sqrt(13), sqrt(5), sqrt(2), 1, 0, sqrt(2),1,sqrt(2),2,sqrt(13)},
        {sqrt(17), 3, 2, sqrt(5), sqrt(2), 0, 1,2,sqrt(2),sqrt(13)},
        {sqrt(20), sqrt(10), sqrt(5), 2, 1, 1,0,1,1,sqrt(8)},
        {5,sqrt(13),sqrt(8),sqrt(5),sqrt(2),2,1,0,sqrt(2),sqrt(8)},
        {sqrt(29),sqrt(17),sqrt(10),3,sqrt(2),sqrt(2),1,sqrt(2),0,sqrt(5)},
        {sqrt(52),sqrt(34),5,sqrt(20),sqrt(13),sqrt(13),sqrt(8),sqrt(8),sqrt(5),0}
    };

    D.setDistances(sampleDistances);
    D.sortDistances();
    std::vector<int>clusters(D.size,0);
    D.Scan(D.eps, D.minPts, clusters);
    D.PrintClusters(clusters);

    end_time = clock();
    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Total time: " << total_time << "s" << std::endl;
    std::cout << "Press any key to exit...";
    getchar(); // waits for user to press any key
    return 0;
}
