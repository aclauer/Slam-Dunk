#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcap.h>
//#include <pcl/io/pcap_io.h>
#include <pcl/point_cloud.h>

/*
pcl::PointCloud<pcl::PointXYZ>::Ptr pcapToPointCloud(const char* path) {
    pcl::PCapReader<pc1::PointXYZ> reader;
    reader.open(path);

    if (!reader.isOpen()) {
        std::cerr << "Failed to open pcap file: " << path << std::endl;
        return NULL;
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pc1::PointXYZ>());
    
    while (!reader.wasStopped()) {
        pcl::PointXYZ point;

        if (reader.readPacket(point)) {
            cloud->push_back(point);
        } else {
            break;
        }
    }

    return cloud;
}
*/
/*
pcl::PointCloud<pcl::PointXYZ>::Ptr pcapToPointCloud(const std::string& pcapPath) {
    // Load the pcap file
    pcl::PCapReader<pcl::PointXYZ> reader;
    reader.open(pcapPath);

    if (!reader.isOpen()) {
        std::cerr << "Failed to open pcap file: " << pcapPath << std::endl;
        return nullptr;
    }

    // Create a point cloud object
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // Loop through each packet in the pcap file
    while (!reader.wasStopped()) {
        pcl::PointXYZ point;

        // Read the next packet
        if (reader.readPacket(point)) {
            // Add the point to the point cloud
            cloud->push_back(point);
        } else {
            break;  // Break the loop when no more packets are available
        }
    }

    return cloud;
}
*/

int main() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/cloud_0000000000.pcd", *cloud) == -1) {
        // Error handling if the file doesn't exist or is not in the correct format
        PCL_ERROR("Could not read PCD file.\n");
        return -1;
    }

    std::cout << "Loaded " << cloud->size() << " data points from cloud.pcd with the following fields: " << std::endl;
    //for (size_t i = 0; i < cloud->fields.size (); ++i) {
    //    std::cout << " " << cloud->fields[i].name;
    //}
    
    printf("1\n");
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Cloud Viewer"));
    //pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
    printf("2\n");

    viewer->setBackgroundColor(0, 0, 0);
    printf("3\n");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_handler(cloud, 255, 255, 255);
    printf("4\n");
    viewer->addPointCloud(cloud, color_handler, "cloud");
    printf("5\n");

    //viewer.showCloud(cloud);

    while (!viewer->wasStopped()) {
        viewer->spinOnce();
    }

    return 0;
}