//
// Created by olcia on 17.01.2020.
//
#include <iostream>
#include <math.h>
#include <iomanip>

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

    double v[size];
    for(int i=0; i<size; i++)
    {
        v[i]={0};
    }

    int maxIterations = 25;
    int iterations = 0;

    double x[size] = {0};

    while (iterations <= maxIterations)
    {
        for (int i = 0; i < size; i++)
        {
            x[i] = (e[i]/A[i][i]);
            for (int j = 0; j < size; j++)
            {
                if (i == j) continue;

                x[i] = x[i] - ((A[i][j] / A[i][i]) * v[j]);
                v[i] = x[i];
            }
        }
        iterations++;
    }

    for(int i = 0;i < size; i++){
        cout << "x" << i+1 << " = " << x[i] << endl;
    }

    cout << "\n-----------------------------\nNormy: " << endl;
    for(int i = 1; i < size; i++)
    {
        cout << i << " " << calculateNorm(v[i] - v[i - 1]) << endl;
    }
    return 0;
}