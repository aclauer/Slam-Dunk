#include "Preprocessor.h"

// Constructor
Preprocessor::Preprocessor() {}

void Preprocessor::testFunction() {
    printf("This is a test function here...\n");
}

// Returns the square distance of a given point
double Preprocessor::getSquareDistance(pcl::PointXYZ point) {
    return pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2);
}

/*
// Creates a vertex map from the given point cloud
double (*Preprocessor::getVertexMap(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud))[900] {
    // TODO: Make this take parameters from parameter object
    double vmap[64][900];   // height = 64, width = 90
    vmap[0][0] = 69.0;
    printf("We are in getVertexMap!\n");
    if (vmap == nullptr) {
        printf("getVertexMap is returning null.\n");
    } else {
        printf("[0, 0] pointer%f\n", vmap[0][0]);
    }
    return vmap;
}
*/

std::vector< std::vector<float> > Preprocessor::getVertexMap(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    std::vector< std::vector<float> > vertexMap(64, std::vector<float>(900));

    printf("Size: %d by %d\n", vertexMap.size(), vertexMap.at(0).size());
    vertexMap[0][0] = 69.0;
    printf("Returning getVertexMap\n");

    return vertexMap;
}
