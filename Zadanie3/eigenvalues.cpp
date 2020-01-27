//
// Created by olcia on 25.12.2019.
//

#include <cmath>
#include <iostream>
#include <iomanip>

constexpr int n = 6;

double calculateNorm(double *arr,int size){
    double norm = 0;
    double tmp = 0;
    for(int i = 0; i < size; i++){
        tmp = arr[i]*arr[i];
        norm += tmp;
    }
    norm = sqrt(norm);
    return norm;
}

double scalarMultiply(double *arr1, double *arr2,int n){
    double sum = 0;
    for(int i=0; i < n; i++){
        sum += arr1[i]*arr2[i];
    }
    return sum;
}

int main() {
    double A[n][n] = {{19.0/12, 13.0/12, 5.0/6, 5.0/6, 13.0/12. -17.0/12},
                    {13.0/12, 13.0/12, 5.0/6, 5.0/6, -11.0/12, 13.0/12},
                    {5.0/6, 5.0/6, 5.0/6, -1.0/6, 5.0/6, 5.0/6},
                    {5.0/6, 5.0/6, -1.0/6, 5.0/6, 5.0/6, 5.0/6},
                    {13.0/12, -11.0/12, 5.0/6, 5.0/6, 13.0/12, 13.0/12},
                    {-17.0/12, 13.0/12, 5.0/6, 5.0/6, 13.0/12, 19.0/12}};

    double y[2][n] = {{1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}};
    double z[n] = {1, 1, 1, 1, 1, 1};
    double u[n] = {1, 1, 1, 1, 1, 1};
    double suma[n] = {0, 0, 0, 0, 0, 0};

    double lambda[2] = {0.0, 0.0}, tmp_lambda[2] = {0.0, 0.0};
    double epsilon = 0.001;

    for (int k = 0; k < 2; k++) {
        do {
            for (int i = 0; i < n; i++) {
                z[i] = 0.0;
                for (int j = 0; j < n; j++) {
                    z[i] += A[i][j] * y[k][j];
                }
            }

            tmp_lambda[k] = lambda[k];

            for (int i = 0; i < n; i++) {
                u[i] = z[i] / calculateNorm(z, n);
            }

            lambda[k] = calculateNorm(z, n) / calculateNorm(y[k], n);

            for (int i = 0; i < k; i++) {
                for (int j = 0; j < n; j++) {
                    suma[j]+=scalarMultiply(y[i],u,n)*y[i][j];
                }
            }

            for (int i = 0; i < n; i++) {
                y[k][i]=u[i]-suma[i];
                suma[i]=0;
            }


        } while (fabs(tmp_lambda[k] - lambda[k]) > epsilon);
    }

    for (int k = 0; k < 2; k++) {
        std::cout << "\nLambda" << k+1 << ": " << std::setprecision(10) << lambda[k] << std::endl;
        std::cout << "Wektor własny dla lambda" << k+1 << ": ";

        for (int i = 0; i < n; i++) {
            std::cout << std::setprecision(10) << y[k][i] << "\t";
        }
    }
}