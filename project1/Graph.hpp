#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <Python.h>
class Graph {
public:
    std::vector<int> FromNodeId;
    std::vector<int> ToNodeId;

    Graph();
    void exceldataload(bool ifprint);
    void exceldataloadcpp(bool ifprint, std::string filename);
};