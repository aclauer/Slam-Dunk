import numpy as np
import open3d as o3d

print("Hello world")




# Load binary point cloud
bin_pcd = np.fromfile("/home/andrewlauer/Documents/projects/Slam-Dunk/pointclouds/000000.bin", dtype=np.float32)

# Reshape and drop reflection values
points = bin_pcd.reshape((-1, 4))[:, 0:3]

# Convert to Open3D point cloud
o3d_pcd = o3d.geometry.PointCloud(o3d.utility.Vector3dVector(points))

# Save to whatever format you like
o3d.io.write_point_cloud("0000000_converted.pcd", o3d_pcd)
