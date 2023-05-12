#include <stdio.h>
#include <vector>
#include <iostream>
#include <time.h>
#include "dbscan.hpp"

int main()
{
    clock_t start_time, end_time;
    double total_time;
    
    // start_time = clock(); 
    Graph G;
    DBSCAN D(0.06, 5);

// ------------------ test data for SCC algorithm------------------
    // std::string filename = "test1.csv";
    // int n = 8;
    // double p = 0.3;

// ------------------- SCC Algorithm ---------------------------
    // Generate a random digraph
    // G.ERDirectedGraph(n,p,filename);
    // try
    // {
    //     G.exceldataloadcpp(false, filename);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cout << "Error: ";
    //     std::cerr << e.what() << '\n';
    // }
    // G.generateAdjacencyList();
    // G.computeSCC();
    // G.printSCC(false);


/// ------------------ test data for DBSCAN algorithm------------------
    //// tested on (2, 3), (3, 4), (4, 4), (4, 5), (5, 5), (6, 4), (6, 5), (6, 6), (7, 5), (8, 7)
    // std::vector<std::vector<double>> sampleDistances = {
    //     {0, sqrt(2), sqrt(5), sqrt(8), sqrt(13), sqrt(17), sqrt(20),5,sqrt(29),sqrt(52)},
    //     {sqrt(2), 0, 1, sqrt(2), sqrt(5), 3, sqrt(10),sqrt(13),sqrt(17),sqrt(34)},
    //     {sqrt(5), 1, 0, 1, sqrt(2), 2, sqrt(5),sqrt(8),sqrt(10),5},
    //     {sqrt(8), sqrt(2), 1, 0, 1, sqrt(5),2,sqrt(5),3,sqrt(20)},
    //     {sqrt(13), sqrt(5), sqrt(2), 1, 0, sqrt(2),1,sqrt(2),2,sqrt(13)},
    //     {sqrt(17), 3, 2, sqrt(5), sqrt(2), 0, 1,2,sqrt(2),sqrt(13)},
    //     {sqrt(20), sqrt(10), sqrt(5), 2, 1, 1,0,1,1,sqrt(8)},
    //     {5,sqrt(13),sqrt(8),sqrt(5),sqrt(2),2,1,0,sqrt(2),sqrt(8)},
    //     {sqrt(29),sqrt(17),sqrt(10),3,sqrt(2),sqrt(2),1,sqrt(2),0,sqrt(5)},
    //     {sqrt(52),sqrt(34),5,sqrt(20),sqrt(13),sqrt(13),sqrt(8),sqrt(8),sqrt(5),0}
    // };

    // std::vector<std::vector<double>> sampleDistances = {
    //     {0,1,1,sqrt(72),sqrt(61),sqrt(61)},
    //     {1,0,sqrt(2),sqrt(61),sqrt(50),sqrt(52)},
    //     {1,sqrt(2),0,sqrt(61),sqrt(52),sqrt(50)},
    //     {sqrt(72),sqrt(61),sqrt(61),0,1,1},
    //     {sqrt(61),sqrt(50),sqrt(52),1,0,sqrt(2)},
    //     {sqrt(61),sqrt(52),sqrt(50),1,sqrt(2),0}
    // };

//// ---------------- existing database for DBSCAN algorithm ---------------------------
    // std::string filename1 = "LondonTrajectoriesDataset.csv";
    // std::string filename1 = "RIOBUSES.csv";
    // std::vector<std::vector<double>> sampleDistances = G.GetSampleDistances(filename1);
    // D.setDistances(sampleDistances);
    // D.sortDistances();
    // std::vector<int>clusters(D.size,0);
    // D.Scan(D.eps, D.minPts, clusters);
    // D.PrintClusters(clusters, false, true, "LondonTrajectoriesDataset_clusters.csv");
    // D.PrintClusters(clusters, false, true, "RIOBUSES_clusters.csv");

    std::vector<double> centerX = {0, 0.5, 1};
    std::vector<double> centerY = {0, 0.5, 1};
    double stddev = 0.1;
    // Number of points for guassian generator
    std::vector<int> num_points_arr = {8,16,32,64,128,256,512,1024,2048,4096};
    // Number of points within square
    std::vector<int> num_points_obt = {};
    std::vector<double>time_vec = {};
    for(auto i :num_points_arr){
        start_time = clock();
        std::vector<std::vector<double>> sampleDistances = D.randompoints(stddev, i, centerX, centerY, true);
        
        D.setDistances(sampleDistances);
        D.sortDistances();
        std::vector<int>clusters(D.size,0);
        D.Scan(D.eps, D.minPts, clusters);
        D.PrintClusters(clusters, false, true, "random_clusters_" + std::to_string(D.size)+".csv");
        end_time = clock();
        total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        time_vec.push_back(total_time);
        num_points_obt.push_back(D.size);
        printf("Total time for %d points: %f s\n", D.size, total_time);
    }
    // file time - num_points_obt in .csv file
    std::ofstream myfile;
    myfile.open("time_num_points.csv", std::ios::trunc);
    myfile << "time,num_points" << std::endl;  
    for(int i = 0; i < time_vec.size(); i++){
        myfile << time_vec[i] << "," << num_points_obt[i] << std::endl;
    }
    myfile.close();


    // end_time = clock();
    // total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    // std::cout << "Total time: " << total_time << "s" << std::endl;
    std::cout << "Press any key to exit...";
    getchar(); // waits for user to press any key
    // Sleep(5000);
    return 0;
}
