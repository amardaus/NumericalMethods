#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
//
// Created by olcia on 25.01.2020.
//

using namespace std;

constexpr int iterations = 10;
constexpr int startingPoints = 8;
constexpr double eps = 1e-32;

class LM
{
private:
    double point[2], minPoint[2], S[2], gradient[2];
    double min = 0.0, Z, hessian = 1.0, err = 1.0;
    int c;

public:
    void findMin()
    {
        srand(time(NULL));
        cout << "Random points; " << endl;
        
        for (int j = 0; j < startingPoints; j++) {
            for (int i = 0; i < 2; i++) {
                point[i] = ((rand() % 20) - 10 + rand() / ((double) RAND_MAX));
            }
            cout << fixed << setprecision(5) << "(" << point[0] << ", " << point[1] << ")" << endl;

            Z = rosenbrock(point);
            int t = 45;
            while ((hessian < eps) || (err > eps)) {
                gradient[0] = (400 * pow(point[0], 3) - 400 * point[0] * point[1] + 2.0 * point[0] - 2.0);
                gradient[1] = (200 * point[1] - 200 * pow(point[0], 2));

                for (int i = 0; i < 2; i++) {
                    S[i] = -gradient[i] / sqrt(pow(gradient[i], 2) + pow(gradient[1], 2));
                }

                double P1[2], P2[2], hessTab[3], error[3], z[3];
                int jacobian = 0;
                c = 0;

                for (int i = 0; i < 2; i++) {
                    P1[i] = point[i] + hessian * S[i];
                    P2[i] = point[i] + 2.0 * hessian * S[i];
                }
                z[1] = rosenbrock(P1);
                z[2] = rosenbrock(P2);

                while ((jacobian < iterations) && (c == 0)) {
                    if (Z <= z[1]) {
                        hessian = hessian / 2.0;
                        z[2] = z[1];
                        for (int i = 0; i < 2; i++) {
                            P2[i] = P1[i];
                            P1[i] = point[i] + hessian * S[i];
                        }
                        z[1] = rosenbrock(P1);
                    }
                    else if (z[2] < z[1]) {
                        z[1] = z[2];
                        hessian = 2.0 * hessian;

                        for (int i = 0; i < 2; i++) {
                            P1[i] = P2[i];
                            P2[i] = point[i] + 2.0 * hessian * S[i];
                        }
                        z[2] = rosenbrock(P2);
                    }
                    else {
                        c = -1;
                    }
                }

                double hmin = 0.0;
                if ((4.0 * z[1] - 2.0 * Z - 2.0 * z[2]) < 0) {
                    hmin = hessian * (4.0 * z[1] - 3.0 * Z - z[2]) / (4.0 * z[1] - 2.0 * Z - 2.0 * z[2]);
                } else {
                    c = 4;
                    hmin = hessian / 3.0;
                }

                for (int i = 0; i < 2; i++) {
                    minPoint[i] = point[i] + hmin * S[i];
                }

                min = rosenbrock(minPoint);
                hessTab[0] = fabs(hmin);
                hessTab[1] = fabs(hmin - hessian);
                hessTab[2] = fabs(hmin - 2.0 * hessian);

                for (int i = 0; i < 3; i++) {
                    if (hessTab[i] < hessian) {
                        hessian = hessTab[i];
                    }
                }

                calculateError(error, z);
                jacobian++;

                t++;
                for (int i = 0; i < 2; i++) {
                    point[i] = minPoint[i];
                }

                Z = min;
                if (t == 50) {
                    t = 0;
                    //cout << fixed << setprecision(10) << min << endl;
                }
            }
        }
    }

    double rosenbrock(double *p)    //x = p[0], y = p[1]
    {
        return pow(1 - p[0], 2) + 100 * pow(p[1] - pow(p[0], 2), 2);
    }

    void calculateError(double error[], double z[])
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
            {
                error[i] = fabs(Z - min);
            }
            error[i] = fabs(z[i] - min);
        }

        for (int i = 0; i < 3; i++)
        {
            if (error[i] < err)
            {
                err = error[i];
            }
            else if ((error[0] + error[1] + error[2]) == 0)
            {
                err = 0;
            }
        }
    }
};

int main()
{
    LM lm;
    lm.findMin();
}
