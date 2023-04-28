#ifndef OPTIMIZER_CLASS_H
#define OPTIMIZER_CLASS_H

#include <eigen3/Eigen/Dense>

class Optimizer {
    public:
        int maxIterations;

        Optimizer(int maxIterations);

        //Eigen::Matrix4d estimateTransformation(std::vector< std::vector<float> > V_d, std::vector< std::vector<float> > V_m, std::vector< std::vector<float> > N_m);
        //double step(std::vector< std::vector<float> > V_d, std::vector< std::vector<float> > V_m, std::vector< std::vector<float> > N_m);

};

#endif