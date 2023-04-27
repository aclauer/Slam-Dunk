# Slam Dunk

SLAM pipeline

# Build and Run instructions

```
cmake --build build
./build/slam_dunk
```

# Point Clouds
We need the point clouds to be in .pcd format before we can load them into a `pcl::PointCloud<PointXYZ>` object. However, point clouds given by KITTI are .bin files.
To do this, run `converter.py` with the appropriate path to the .bin file. This will output a .pcd file with the corresponding data, that can then be fed into the project.

# Dependencies I downloaded

```
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
sudo apt-get install libpcl-dev
sudo apt-get install libpcap-dev
sudo apt-get install pcl-tools
sudo apt-get install libopencv-dev

```

# Resources
J. Behley and C. Stachniss, [“Efficient Surfel-Based SLAM using 3D Laser Range Data in Urban Environments,”](http://www.roboticsproceedings.org/rss14/p16.pdf) in Robotics: Science and Systems XIV, Robotics: Science and Systems Foundation, Jun. 2018. doi: 10.15607/RSS.2018.XIV.016.

[PCD Downloads](https://sourceforge.net/projects/pointclouds/files/)

https://github.com/yanii/kitti-pcl
