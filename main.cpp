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


void addOrigin(pcl::visualization::PCLVisualizer::Ptr viewer, double scale) {
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
    /*
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/cloud_0000000001.pcd", *cloud) == -1) {
        // Error handling if the file doesn't exist or is not in the correct format
        PCL_ERROR("Could not read PCD file.\n");
        return -1;
    }

    std::cout << "Loaded " << cloud->size() << " data points from cloud.pcd with the following fields: " << std::endl;
    //for (size_t i = 0; i < cloud->fields.size (); ++i) {
    //    std::cout << " " << cloud->fields[i].name;
    //}
    */

    printf("1\n");
    //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    //pcl::io::loadPCDFile("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/000000.bin", cloud);
    printf("Loaded?\n");
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = loadPCD("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/0000000_converted.pcd");
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Cloud Viewer"));
    //pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");https://sourceforge.net/projects/pointclouds/files/
    printf("2\n");

    viewer->setBackgroundColor(0, 0, 0);
    printf("3\n");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_handler(cloud, 212, 201, 87);
    printf("4\n");
    viewer->addPointCloud(cloud, color_handler, "cloud");
    printf("5\n");

    //pcl::PointXYZ center = pcl::PointXYZ(0, 0, 0);
    //viewer->addSphere(center, 0.01, 255, 0, 0);
    addOrigin(viewer, 5);

    //viewer.showCloud(cloud);

    while (!viewer->wasStopped()) {
        viewer->spinOnce();
    }

    return 0;
}