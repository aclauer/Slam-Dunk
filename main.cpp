#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcap.h>
#include <pcl/point_cloud.h>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "Preprocessor.h"

pcl::PointCloud<pcl::PointXYZ>::Ptr loadPCD(const char* path) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ>(path, *cloud) == -1) {
        // Error handling if the file doesn't exist or is not in the correct format
        PCL_ERROR("Could not read PCD file.\n");
        return NULL;
    }

    std::cout << "Loaded " << cloud->size() << " data points." << std::endl;

    return cloud;
}

void addAxes(pcl::visualization::PCLVisualizer::Ptr viewer, double scale) {
    pcl::PointXYZ center = pcl::PointXYZ(0, 0, 0);
    pcl::PointXYZ x = pcl::PointXYZ(scale, 0, 0);
    pcl::PointXYZ y = pcl::PointXYZ(0, scale, 0);
    pcl::PointXYZ z = pcl::PointXYZ(0, 0, scale);
    viewer->addSphere(center, 0.01, 255, 0, 0);
    viewer->addArrow(x, center, 255, 0, 0, false, "x");
    viewer->addArrow(y, center, 0, 255, 0, false, "y");
    viewer->addArrow(z, center, 0, 0, 255, false, "z");
}

int main() {
    // Load in the specified point cloud after it has been converted to pcd
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = loadPCD("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/0000000_converted.pcd");
    
    Preprocessor preprocessor;

    // Print out some sample point coordinates
    for (int nIndex = 0; nIndex < cloud->points.size(); nIndex++) {
        //double x = cloud->points[nIndex].x;
        //double y = cloud->points[nIndex].y;
        //double z = cloud->points[nIndex].z;
        //printf("x: %f\n", cloud->points[nIndex].x);
        //printf("y: %f\n", cloud->points[nIndex].y);
        //printf("z: %f\n", cloud->points[nIndex].z);
        //printf("Range: %f\n", preprocessor.getSquareDistance(cloud->points[nIndex]));
    }

    std::vector<std::vector<float> > vertexMap = preprocessor.getVertexMap(cloud);

    // Convert vertex map into Mat object
    cv::Mat img(vertexMap.size(), vertexMap.at(0).size(), CV_8UC1);
    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++) {
            img.at<uchar>(i, j) = (vertexMap.at(i).at(j) * 30);
        }
    }

    cv::imshow("Vertex Map", img);
    cv::waitKey(0);  // wait for a key press
    
    // Create visualizer
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Visualization"));

    // Set background color to be black
    viewer->setBackgroundColor(0, 0, 0);

    // Set point cloud color
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_handler(cloud, 212, 201, 87);
    viewer->addPointCloud(cloud, color_handler, "cloud");

    // Add x, y, z arrows to point cloud
    addAxes(viewer, 3);

    // Display point cloud
    while (!viewer->wasStopped()) viewer->spinOnce();
    return 0;
}