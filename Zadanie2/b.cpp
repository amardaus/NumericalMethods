//
// Created by olcia on 17.01.2020.
//
#include <iostream>
#include <math.h>

using namespace std;

constexpr int size = 128;

double calculateNorm(double arr){
    double t = 0;
    for(int i=0; i<size; i++)
    {
        t += arr * arr;
    }
    return sqrt(t);
}

int main()
{
    double A[size][size]={0};

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(i==j){
                A[i][j]={4};
            }
            else if(j==i+1 || j==i+5 || i==j+1 || i==j+5){
                A[i][j]={1};
            }
        }
    }

    double e[size];
    for(int i=0; i<size; i++)
    {
        e[i] = 1;
    }

    int iterations = 0;
    int maxIterations = 25;

    double tmp1[size]={0};
    double tmp2[size]={0};
    double result[size]={0};


    for(int i=0; i < size; i++)
        tmp2[i] = tmp1[i] = e[i];

    while (iterations < maxIterations)
    {
        double r = 0.0;
        double p = 0.0;

        for(int i=0; i < size; i++)
            r += tmp1[i] * tmp1[i];

        for(int i=0; i < size; i++)
        {
            for(int j=0; j < size; j++)
                p += A[i][j] * tmp2[i] * tmp2[j];
        }
        double alpha = r / p ;

        double tmp3[size] = {0};
        for(int i=0; i < size; i++)
        {
            result[i] += alpha * tmp2[i];
            tmp3[i] = tmp1[i];
            for(int j=0; j < size; j++)
                tmp3[i] -= alpha * A[i][j] * tmp2[j];
        }
        double rr = 0.0;

        for(int i=0; i < size; i++)
            rr += tmp3[i] * tmp3[i];

        double beta = rr / r;

        for(int i=0; i < size; i++)
        {
            tmp2[i] = beta * tmp2[i] + tmp3[i];
            tmp1[i] = tmp3[i];
        }
        iterations++;
    }

    for(int i = 0; i < size; i++){
        cout << "x" << i+1 << " = " << result[i] << endl;
    }

    cout << "\n-----------------------------\nNormy: " << endl;
    for(int i = 1; i < size; i++)
    {
        cout << i << " " << calculateNorm(result[i] - result[i - 1]) << endl;
    }
    return 0;
}