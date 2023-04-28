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
}

std::vector< std::vector<float> > Preprocessor::getVertexMap(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    std::vector< std::vector<float> > vertexMap(64, std::vector<float>(900));
    
    for (int i = 0; i < cloud->points.size(); i++) {
        pcl::PointXYZ p = cloud->points[i];
        double r = this->getDistance(p);
        int u = this->projectUCoord(p);
        int v = this->projectVCoord(p);

        u = (u < 0) ? 0 : u;
        u = (u > 899) ? 899 : u;
        v = (v < 0) ? 0 : v;
        v = (v > 63) ? 63 : v;

        vertexMap.at(v).at(u) = r;
    }
    return vertexMap;
}
