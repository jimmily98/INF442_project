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
};