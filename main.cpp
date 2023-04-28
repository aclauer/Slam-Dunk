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
    preprocessor.testFunction();

    // Print out some sample point coordinates
    for (int nIndex = 0; nIndex < cloud->points.size(); nIndex++) {
        //double x = cloud->points[nIndex].x;
        //double y = cloud->points[nIndex].y;
        double z = cloud->points[nIndex].z;
        //printf("x: %f\n", cloud->points[nIndex].x);
        //printf("y: %f\n", cloud->points[nIndex].y);
        //printf("z: %f\n", cloud->points[nIndex].z);
        //printf("Range: %f\n", preprocessor.getSquareDistance(cloud->points[nIndex]));
    }
    pcl::PointXYZ p = cloud->points[3684];
    double x = p.x;
    double y = p.y;
    double z = p.z;

    //double arr[4][2] = {{1/10, 2/10}, {3/10, 4/10}, {5/10, 6/10}, {7/10, 8/10}};

    //cv::Mat image(3, 4, CV_16U, arr);
    //cv::imshow("Test", image);
    //cv::waitKey(0);

    int rows = 100;
    int cols = 100;
    //cv::Mat arr(rows, cols, CV_8UC1);
    //cv::randu(arr, cv::Scalar(0), cv::Scalar(255));  // fill the array with random values between 0 and 255

    // display the array as an image
    //cv::namedWindow("Array Image", cv::WINDOW_NORMAL);
    //cv::imshow("Array Image", arr);
    //cv::waitKey(0);  // wait for a key press

    

    //printf("Type: %s\n", typeid(preprocessor.getVertexMap(cloud)));
    
    //double vertexMap[64][900];

    //double(*vertexMap)[900] = preprocessor.getVertexMap(cloud);
    //printf("a\n");
    std::vector<std::vector<float> > vertexMap = preprocessor.getVertexMap(cloud);
    printf("value from vertex map: %f\n", vertexMap[0][0]);
    //printf("b\n");
    /*
    if (vertexMap == NULL) {
        printf("Null\n");
    } else {
        printf("Not null!\n");
    }*/
    //printf("About to print\n");
    //printf("%f\n", vertexMap[0][0]);
    //printf("(%f, %f, %f)\n", x, y, z);

    //double z_1 = z / abs(x);double r = preprocessor.getSquareDistance(p);
    //double s = asin(z * 1/r);
    //printf("z_1: %f\n", z_1);
    //double z_2 = z_1 + (24.8 / 26.8);
    //double z_3 = z_2 * 64;
    //printf("z_1: %f, z_2: %f, z_3: %f\n", z_1, z_2, z_3);

    //double r = preprocessor.getDistance(p);
    //double s = asin(z * 1/r);

    //double v = (1 - (asin(z * (1/r)) + 2)/26.8)*64;
    //printf("r: %f, s: %f, v: %f\n", r, s, v);

    //double theta = asin(z / r);
    //double z_1 = tan(theta);

    //printf("r: %f, Theta: %f, z_1: %f\n", r, theta, z_1);

    //double min = 0;
    //double max = 0;
    /*
    for (int i = 0; i < cloud->points.size(); i++) {
        double z = cloud->points[i].z;
        double r = preprocessor.getDistance(cloud->points[i]);
        double theta = asin(z / r);
        double z_1 = tan(theta);

        min = (z_1 < min) ? z_1 : min;
        max = (z_1 > max) ? z_1 : max;
    }

    printf("Min z_1: %f\n", min);
    printf("Max z_1: %f\n", max);

    // tan(24.8 deg)
    double min_v = (min + 0.462064869823) * 128.7763;
    double max_v = (max + 0.462064869823) * 128.7763;

    printf("Min_v: %f\n", min_v);
    printf("Max_v: %f\n", max_v);

    printf("Successfully finished!\n");

    // Algo for u coordinate
    double t = atan2(y, x);
    double u_1 = 1 - (t / 3.1415926);
    double u = u_1 * 900 / 2;
    printf("t: %f, u_1: %f, u: %f\n", t, u_1, u);
    */
    //printf("1\n");
    //cv::Mat img(64, 900, CV_8UC1);
    //cv::Mat img(cv::Size(900, 64), CV_8U, vertexMap);
    
    //printf("%d, %d\n", vertexMap.size(), vertexMap.at(0).size());
    
    for (int i = 0; i < 100; i++) {
        printf("Intensity: %f\n", vertexMap[0][i]);
    }
    printf("value from vertex map2: %f\n", vertexMap[0][0]);
    printf("Sampling vertex map: %f\n", vertexMap[0][0]);
    cv::Mat img(vertexMap.size(), vertexMap.at(0).size(), CV_8UC1);
    
    printf("2\n");
    printf("Sampling vertex map: %f\n", vertexMap[0][0]);
    for (int i = 1; i < 1+1; i++) {
        for (int j = 0; j < img.cols; j++) {
            //printf("Vertex value now please: %d %f\n", j, vertexMap[i][j]);
        }
    }
    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++) {
            //printf("vertexMap value: %f\n", vertexMap.at(i).at(j));
            //img.at<uchar>(i, j) = vertexMap.at(i).at(j);
            //printf("%f\n", vertexMap.at(2).at(2) * 20);
            img.at<uchar>(i, j) = (vertexMap.at(i).at(j) * 30);
        }
    }
        
    //printf("%d, %d\n", img.size(), img.at(0).size());
    /*
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 900; j++) {
            vertexMap_Mat.at<double>(i, j) = vertexMap.at(i).at(j);
        }
    }*/

    

    printf("3\n");
    //cv::namedWindow("Array Image", cv::WINDOW_NORMAL);
    //cv::namedWindow("Window Test");
    printf("5\n");
    cv::imshow("Array Image", img);
    
    // Create visualizer
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Visualization"));

    // Set background color to be black
    viewer->setBackgroundColor(0, 0, 0);

    // Set point cloud color
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_handler(cloud, 212, 201, 87);
    viewer->addPointCloud(cloud, color_handler, "cloud");

    // Add x, y, z arrows to point cloud
    addAxes(viewer, 3);
    printf("Height: %d\n", cloud->height);
    printf("Width: %d\n", cloud->width);

    // Display point cloud
    while (!viewer->wasStopped()) viewer->spinOnce();
    cv::waitKey(0);  // wait for a key press
    printf("6\n");
    
    printf("7\n");
    return 0;
}