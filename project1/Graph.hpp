#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <Python.h>
#include <random>
class Graph {
public:
    std::vector<int> FromNodeId;
    std::vector<int> ToNodeId;
    int size;
    std::vector<int> vertices;
    std::vector<std::vector<int>> adjacencyList;
    std::vector<std::vector<int>>  verticesto;
    std::vector<std::vector<int>>  SCC;
    std::vector<std::vector<double>> distanceMatrix;
    std::vector<std::vector<double>> sortedDistances;
    std::vector<std::vector<int>> sortedIndices;

    Graph();
    void exceldataload(bool ifprint);
    void exceldataloadcpp(bool ifprint, std::string filename);
    void printEdges();
    void generateAdjacencyList();
    void printVector(const std::vector<int>& vec) const;
    void printNestedVector(const std::vector<std::vector<int>>& nested_vector) const;
    void DFS(int i);
    void computeSCC();
    void printSCC();
    double RandomGene();
    void ERDirectedGraph(int n, double p, std::string filename);
    void printDistanceMatrix() const;
    void setDistances(const std::vector<std::vector<double>>& inputDistances);
    void sortDistances();
    void printSortedDistances() const;
    void printSortedIndices() const;
    // str1, str2: column names of the two columns of coordinates
    std::vector<std::vector<double>> GetSampleDistances(std::string filename);


};