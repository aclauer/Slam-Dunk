#ifndef PREPROCESSOR_CLASS_H
#define PREPROCESSOR_CLASS_H

#include <cmath>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class Preprocessor {
    public:
        Preprocessor();

        void testFunction();
        double getSquareDistance(pcl::PointXYZ point);
        double** getVertexMap(pcl::PointCloud<pcl::PointXYZ> cloud);
};

#endif