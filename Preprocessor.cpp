#include "Preprocessor.h"

// Constructor
Preprocessor::Preprocessor() {}

void Preprocessor::testFunction() {
    printf("This is a test function here...\n");
}

// Returns the  distance of a given point
double Preprocessor::getDistance(pcl::PointXYZ point) {
    return sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));
}

int Preprocessor::projectUCoord(pcl::PointXYZ point) {
    double x = point.x;
    double y = point.y;
    return floor((1 - (atan2(y, x) / M_PI)) * 900 / 2);
}

int Preprocessor::projectVCoord(pcl::PointXYZ point) {
    
    double z = point.z;
    double r = this->getDistance(point);
    return 64 - floor((tan(asin(z / r)) + 0.4620649) * 128.7763);
    

    //double z = point.z;
    //double r = this->getDistance(point);
    //return floor(((1 - (asin(z / r) + 3) / 28)) * 64);
}

std::vector< std::vector<float> > Preprocessor::getVertexMap(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    printf("We are in getVertexMap\n");
    std::vector< std::vector<float> > vertexMap(64, std::vector<float>(900));
    printf("Created vertexMap vector\n");
    printf("Size: %ld by %ld\n", vertexMap.size(), vertexMap.at(0).size());
    
    for (int i = 0; i < cloud->points.size(); i++) {
        //printf("%d\n", i);
        pcl::PointXYZ p = cloud->points[i];
        //printf("got a point\n");
        double r = this->getDistance(p);
        //printf("computed distance\n");
        int u = this->projectUCoord(p);
        //printf("computed u: %d\n", u);
        int v = this->projectVCoord(p);
        //printf("computed v: %d\n", v);

        u = (u < 0) ? 0 : u;
        u = (u > 899) ? 899 : u;
        v = (v < 0) ? 0 : v;
        v = (v > 63) ? 63 : v;

        //printf("Updated (u, v): (%d, %d)\n", u, v);

        vertexMap.at(v).at(u) = r;
        //printf("set value: %f\n", r);
    }

    printf("Returning getVertexMap\n");

    return vertexMap;
}
