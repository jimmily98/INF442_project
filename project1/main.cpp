#include <stdio.h>
#include <vector>
#include <iostream>
#include "Graph.hpp"

using namespace std;

int main()
{
    try
    {
        Graph G;
        G.exceldataload(true);
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: ";
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "Press any key to exit...";
    getchar(); // waits for user to press any key
    return 0;
}
