#include "Preprocessor.h"

// Constructor
Preprocessor::Preprocessor() {}

void Preprocessor::testFunction() {
    printf("This is a test function here...\n");
}

// Creates a vertex map from the given point cloud

double** getVertexMap(pcl::PointCloud<pcl::PointXYZ> cloud) {
    // TODO: Make this take parameters from parameter object
    double vmap[64][900];   // height = 64, width = 900

    printf("We are in getVertexMap!\n");
    //return vmap;
    return NULL;
}
