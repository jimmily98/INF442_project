# include"dbscan.hpp"

DBSCAN::DBSCAN(double eps, int minPts) {
    this->eps = eps;
    this->minPts = minPts;
}

// find the neighbors of the point (idx = i)
std::vector<int> DBSCAN::Findneighbors(int i, double eps, int minPts) {
    std::vector<int> neighbors;
    for (int j = 0; j < size; j++) {
        if (distanceMatrix[i][j] <= eps && distanceMatrix[i][j] > 0) {
            neighbors.push_back(j);
        }
    }
    return neighbors;
}   

// expand the cluster
// cluster[i] = -1 means that the point is noise; 
// cluster[i] = 0 means that the point is not visited yet;
// cluster[i] = k means that the point is in the kth cluster
void DBSCAN::Expandclusters(int i, int id, std::vector<int>& clusters, double eps, int minPts) {
    std::vector<int> neighbors = Findneighbors(i, eps, minPts);
    if(neighbors.size() < minPts) {
        clusters[i] = -1;
        return;
    }
    else{
        clusters[i] = id;
        for (int j = 0; j < neighbors.size(); j++) {
            if (clusters[neighbors[j]] == 0) {
                clusters[neighbors[j]] = id;
                Expandclusters(neighbors[j], id, clusters, eps, minPts);
            }
        }
    }
}

// scan the whole graph
void DBSCAN::Scan(double eps, int minPts, std::vector<int>& clusters) {
    int id = 0;
    for (int i = 0; i < size; i++) {
        if (clusters[i] == 0) {
            std::vector<int> neighbors = Findneighbors(i, eps, minPts);
            if(neighbors.size() < minPts)
                clusters[i] = -1;
            else{
                id++;
                Expandclusters(i, id, clusters, eps, minPts);
            }

        }
    }
}

// print the clusters
void DBSCAN::PrintClusters(std::vector<int>& clusters) {
    std::cout << "The clusters are: " << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << clusters[i] << " ";
    }
    std::cout << std::endl;
}