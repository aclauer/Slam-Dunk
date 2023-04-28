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
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = loadPCD("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/0000000019_converted.pcd");
    
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
    cv::Mat vertImg(vertexMap.size(), vertexMap.at(0).size(), CV_8UC1);
    for (int i = 0; i < vertImg.rows; i++){
        for (int j = 0; j < vertImg.cols; j++) {
            vertImg.at<uchar>(i, j) = (vertexMap.at(i).at(j) * 30);
        }
    }

    cv::imshow("Vertex Map", vertImg);
    cv::waitKey(0);  // wait for a key press

    std::vector<std::vector<float> > normalMap = preprocessor.getNormalMap(vertexMap);

    cv::Mat normImg(normalMap.size(), normalMap.at(0).size(), CV_8UC1);
    for (int i = 0; i < normImg.rows; i++) {
        for (int j = 0; j < normImg.cols; j++) {
            normImg.at<uchar>(i, j) = (normalMap.at(i).at(j));
        }
    }

    cv::imshow("Normal Map", normImg);
    cv::waitKey(0);
    
    
    // Create visualizer
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Visualization"));
    // Set point cloud color
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_handler(cloud, 0, 0, 0);
    viewer->addPointCloud(cloud, color_handler, "cloud");
    // Set background color to be white
    viewer->setBackgroundColor(255, 255, 255);
    viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 0.125, "cloud");

    // Add x, y, z arrows to point cloud
    addAxes(viewer, 3);

    // Display point cloud
    while (!viewer->wasStopped()) viewer->spinOnce();
    return 0;
}