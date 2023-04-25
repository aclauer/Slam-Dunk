#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcap.h>


pcl::PointCloud<pcl::PointXYZ>::Ptr pcap_to_point_cloud(const char* path) {
    //char errbuf[PCAP_ERRBUF_SIZE];
    
}


int main() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("/home/andrewlauer/Documents/projects/Slam-Dunk/CSite1_orig-utm.pcd", *cloud) == -1) {
        // Error handling if the file doesn't exist or is not in the correct format
        PCL_ERROR("Could not read PCD file.\n");
        return -1;
    }

    std::cout << "Loaded " << cloud->size() << " data points from cloud.pcd with the following fields: " << std::endl;
    //for (size_t i = 0; i < cloud->fields.size (); ++i) {
    //    std::cout << " " << cloud->fields[i].name;
    //}

    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Cloud Viewer"));

    viewer->setBackgroundColor(0, 0, 0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> color_handler(cloud, 255, 255, 255);
    viewer->addPointCloud(cloud, color_handler, "cloud");

    //viewer.showCloud(cloud);

    while (!viewer->wasStopped()) {
        viewer->spinOnce();
    }

    return 0;
}