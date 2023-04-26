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

// Creates a vertex map from the given point cloud
double** Preprocessor::getVertexMap(pcl::PointCloud<pcl::PointXYZ> cloud) {
    // TODO: Make this take parameters from parameter object
    double vmap[64][900];   // height = 64, width = 900

    printf("We are in getVertexMap!\n");
    //return vmap;
    return NULL;
}
