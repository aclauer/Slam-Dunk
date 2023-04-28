#include "Optimizer.h"

int maxIterations;

Optimizer::Optimizer(int maxIterations) {
    this->maxIterations = maxIterations;
}

Eigen::Matrix4d estimateTransformation(Eigen::Matrix4d T0, std::vector< std::vector<float> > V_d, std::vector< std::vector<float> > V_m, std::vector< std::vector<float> > N_m) {
    Eigen::MatrixXd transformation(T0);
    int k = 0;
    for (;;) {
        if (k > maxIterations) {
            break;  // reached max iterations
        }

        double error = this->step();

        if (error == 0) {
            break;  // converged
        }
        k++;
    }
    
    return 0;
}