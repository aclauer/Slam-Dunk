#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcap.h>
#include <pcl/point_cloud.h>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <ctime>

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
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = loadPCD("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/049.pcd");
    
    Preprocessor preprocessor;

    std::clock_t startV = std::clock();
    std::vector<std::vector<float> > vertexMap = preprocessor.getVertexMap(cloud);
    std::clock_t endV = std::clock();

    double vmap_runtime = double(endV - startV) / CLOCKS_PER_SEC;
    printf("Vertex Map runtime: %f\n", vmap_runtime);

    // Convert vertex map into Mat object
    cv::Mat vertImg(vertexMap.size(), vertexMap.at(0).size(), CV_8UC3);
    for (int i = 0; i < vertImg.rows; i++){
        for (int j = 0; j < vertImg.cols; j++) {
            double c = vertexMap.at(i).at(j) * 30;
            vertImg.at<cv::Vec3b>(i, j) = cv::Vec3b(c, c, c);
            if (j == 450) {
                vertImg.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 255);
            }
            if (j == 225) {
                vertImg.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 255, 0);
            }
        }
    }

    cv::imshow("Vertex Map", vertImg);
    cv::waitKey(0);  // wait for a key press
    
    //cv::imwrite("/maps/000_vert.png", vertImg);

    std::clock_t startN = std::clock();
    std::vector<std::vector<float> > normalMap = preprocessor.getNormalMap(vertexMap);
    std::clock_t endN = std::clock();

    double nmap_runtime = double(endN - startN) / CLOCKS_PER_SEC;
    printf("Normal Map runtime: %f\n", nmap_runtime);

    cv::Mat normImg(normalMap.size(), normalMap.at(0).size(), CV_8UC3);
    for (int i = 0; i < normImg.rows; i++) {
        for (int j = 0; j < normImg.cols; j++) {
            double c = (normalMap.at(i).at(j));
            normImg.at<cv::Vec3b>(i, j) = cv::Vec3b(c, c, c);
            if (j == 450) {
                normImg.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 255);
            }
            if (j == 225) {
                normImg.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 255, 0);
            }
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