// MZMTIN002

#include "Eigen/Dense"
#include <vector>
#include <iostream>

using namespace std;

vector<double> january = {51.2, 51.2, 39.5, 45.1, 29.9, 24.8, 32, 35.6, 54.6, 67.2, 42.4, 29, 22.9, 23.8, 27.9, 19.4, 31.3, 33.3, 52.9, 21.5, 33.4, 29.2, 25.5, 14.2, 8.5, 12.2, 47.1, 27.8, 31.3, 20.5, 22.6, 31.9, 20.6, 32.7, 35.2, 21.5, 23.7, 32.2, 42.1, 40.5, 8.2, 31.1, 26.9, 28.4, 36.8, 38.1, 32.3, 28.1, 28.4, 45.4, 14.2, 40.5, 38.3, 44.8, 43.6, 52.1, 28, 16.8, 40.5, 37.5, 25.4, 34.5, 19.4, 26.6}; 
vector<double> june  = {81.6, 91.2, 81.4, 75.2, 73, 72.7, 75.8, 78.7, 81, 82.3, 78, 74.5, 71.9, 75.1, 75, 75.1, 80.7, 76.9, 81.9, 68, 76.6, 73.3, 73.3, 63.8, 65.6, 71.9, 81.7, 78.8, 78.6, 69.3, 77.2, 69.3, 69.7, 75.1, 78.7, 72, 70.1, 76.6, 78.5, 77.5, 70.8, 75.6, 71.4, 73.6, 81.5, 67.1, 76.8, 71.9, 72.1, 81.2, 73.3, 79.6, 79.6, 84.8, 82.3, 83.3, 76.7, 69.8, 78.3, 77.9, 69.7, 75, 69.9, 69.1};

int main() {
    const unsigned int noRows = january.size();
    const unsigned int noCols = 2;
    Eigen::MatrixXf initialMatrix;
    initialMatrix.resize(noRows, noCols);
    for (int i = 0; i < noRows; ++i) { // Populate matrix with values from data file.
        for (int j = 0; j < 1; ++j) {
            initialMatrix(i, j) = january[i];
            initialMatrix(i, j + 1) = june[i];
        }
    }

    Eigen::VectorXf means(noCols); // Obtain means of the data column-wise.
    means = initialMatrix.colwise().mean();

    for (int i = 0; i < noRows; ++i) { // Subtract mean from data points.
        for (int j = 0; j < 1; ++j) {
            initialMatrix(i, j) -= means[j];
            initialMatrix(i, j + 1) -= means[j + 1];
        }
    }

    Eigen::MatrixXf centered = initialMatrix.rowwise() - initialMatrix.colwise().mean(); // Calculate sample covariance matrix.
    Eigen::MatrixXf cov = (centered.adjoint() * centered) / double(noRows - 1);

    cout << "Sample Covariance Matrix" << endl;
    cout << cov << endl;

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> eig(cov);

    Eigen::MatrixXf eigValues = eig.eigenvalues();
    Eigen::MatrixXf eigVectors = eig.eigenvectors().rightCols(2); // Computing eigenvectors and eigenvalues.

    cout << "Eigen Vectors" << endl;
    cout << eigVectors << endl;
    cout << "Eigen Values" << endl;
    cout << eigValues << endl;

    double totalVariance = eigValues.sum();
    cout << "Total Variance" << endl;
    cout << totalVariance << endl;

    return 0;
}