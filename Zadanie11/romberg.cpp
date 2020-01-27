//
// Created by olcia on 13.01.2020.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

constexpr double epsilon = 0.0000001;
constexpr int kroki = 20;

double findA()
{
    double A = 0.0;
    while(exp(-A) > epsilon){
        A++;
    }
    return A;
}

double f(double x)
{
    return sin(M_PI*(1+sqrt(x))/(1+x*x))*exp(-x);
}

double trapez(double A, double h)
{
    double Sn = 0.0;

    for (double i = h; i < A; i += h)
    {
        Sn += f(i);
    }

    Sn += f(0)/2;
    Sn += f(A)/2;
    Sn *= h;

    return Sn;
}

double romberg(double A)
{
    double a = 0;
    double b = A;
    double h = (b - a);
    double R[kroki];
    double tmp;

    for(int i = 0; i < kroki; i++){
        R[i] = 1.0;
    }

    for (int i = 1; i < kroki; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (j == 1.0)
            {
                tmp = R[j];
                R[j] = trapez(A, h / pow(2, i - 1));
            }
            else
            {
                R[i] = (pow(4, j - 1) * R[j - 1] - tmp) / (pow(4, j - 1) - 1);
                tmp = R[j];
                R[j] = R[i];
            }
        }
    }

    return R[kroki - 1];
}

int main()
{
    double A = findA();
    cout << "A: " << A << endl;
    cout << "I1: " << romberg(A) << endl;

    return 0;
}