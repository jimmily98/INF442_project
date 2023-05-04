# include"Graph.hpp"

class DBSCAN : public Graph {

public:

double eps;
int minPts;

DBSCAN(double eps, int minPts);
std::vector<int> Findneighbors(int i, double eps, int minPts);
void Expandclusters(int i, int cluster,std::vector<int>& clusters, double eps, int minPts);
void Scan(double eps, int minPts, std::vector<int>& clusters);
void PrintClusters(std::vector<int>& clusters);

};
