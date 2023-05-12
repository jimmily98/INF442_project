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
void DBSCAN::PrintClusters(std::vector<int>& clusters, bool verbose, bool tofile, std::string filename) {
    if(verbose){
        // print the list of clusters
        std::cout << "The clusters are: " << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << clusters[i] << " ";
        }
        std::cout << std::endl;
    }
    else{
        // print the number of points in each cluster
        int n_cluster = std::max_element(clusters.begin(), clusters.end())[0];
        int noise = std::count(clusters.begin(), clusters.end(), -1);
        std::cout << "The number of outliers is: " << noise << std::endl;
        for(int i = 1; i < n_cluster + 1; i++){
            int n_points = std::count(clusters.begin(), clusters.end(), i);
            std::cout << "The number of points in cluster " << i << " is: " << n_points << std::endl;
        }
    if(tofile){
        std::ofstream myfile(filename, std::ios::trunc);  
        myfile << "clusters," << "minpts," << "eps" << std::endl;
        for (auto i = clusters.begin(); i != clusters.end(); ++i) {
            if(i == clusters.begin()){
                myfile << *i << "," << minPts << "," << eps << std::endl;
            }
            else{
                myfile << *i << std::endl;  
            }  
        }
        myfile.close();  
    }

    }
}