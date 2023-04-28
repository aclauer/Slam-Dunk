#ifndef PREPROCESSOR_CLASS_H
#define PREPROCESSOR_CLASS_H

#include <cmath>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class Preprocessor {
    public:
        Preprocessor();

        void testFunction();
        double getDistance(pcl::PointXYZ point);
        //double (*getVertexMap(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud))[900];
        std::vector< std::vector<float> > getVertexMap(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
        int projectUCoord(pcl::PointXYZ point);
        int projectVCoord(pcl::PointXYZ point);
};

#endif