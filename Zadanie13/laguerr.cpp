#include <iostream>
#include <complex>
#include <vector>
#include <iomanip>
//
// Created by olcia on 05.01.2020.
//

using namespace std;

typedef complex<double> complexNumber;
typedef vector<complex<double>> complexVector;
double epsilon = 0.00000001;

class Laguerr
{
private:
    complexNumber tmp;
    complexNumber randomValue;

    complexNumber derivative(complexVector values, int control)
    {
        switch (control)
        {
            case 0:
                tmp = values[values.size() - 1];
                break;
            case 1:
                tmp = values[values.size() - 1] * (double)(values.size() - 1);
                break;
            case 2:
                tmp = values[values.size() - 1] * (double)(values.size() - 1) * (double)(values.size() - 2);
                break;
        }

        for (double i = values.size() - 2; i >= control; i--)
        {
            switch (control)
            {
                case 0:
                    tmp = tmp * randomValue + values[i];
                    break;
                case 1:
                    tmp = tmp * randomValue + values[i] * i;
                    break;
                case 2:
                    tmp = tmp * randomValue + values[i] * i * (i - 1);
                    break;
            }
        }
        return tmp;
    }

    void print(complex<double> x1, complex<double> x2)
    {
        printX(x1);
        printX(x2);
    }

    void printX(complex<double> x)
    {
        if ((x.real() == 0.0 || x.real() == -0.0) && (x.imag() == 0.0 || x.imag() == -0.0))
        {
            cout << fixed << "0.0" << endl;
        }
        else if ((x.real() == 0.0 || x.real() == -0.0) && (x.imag() != 0.0 || x.imag() != -0.0))
        {
            cout << fixed << setprecision(10) << x.imag() << "i" << endl;
        }
        else if ((x.imag() == 0.0 || x.imag() == -0.0) && (x.real() != 0.0 || x.real() != -0.0))
        {
            cout << fixed << setprecision(6) << x.real() << endl;
        }
        else
        {
            cout << fixed << setprecision(6) << x.real() << " + " << fixed << setprecision(10) << x.imag() << "i" << endl;
        }
    }

    complexNumber laguerr(complexVector values)
    {
        complexNumber sq = sqrt((double)(values.size() - 2) * ((double)(values.size() - 2) * derivative(values, 1) * derivative(values, 1) - (double)(values.size() - 1) * derivative(values, 0) * derivative(values, 2)));
        complexNumber firstP = derivative(values, 1);

        if (abs(firstP + sq) > abs(firstP - sq))
        {
            return randomValue - ((double)(values.size() - 1) * derivative(values, 0)) / (firstP + sq);
        }
        else
        {
            return randomValue - ((double)(values.size() - 1) * derivative(values, 0)) / (firstP - sq);
        }
    }

    double randZeroToOne()
    {
        return rand() / (RAND_MAX + 1.);
    }

public:
    void solve(complexVector values)
    {
        while (values.size() - 1 > 2)
        {
            complexNumber x0(randZeroToOne(), randZeroToOne());

            while (abs(derivative(values, 0)) > epsilon)
            {
                randomValue = x0;
                x0 = laguerr(values);
            }

            //wygladzanie
            complexVector vecTmp = values;
            values.resize(values.size() - 1);
            values[values.size() - 1] = vecTmp[values.size()];

            for (int i = values.size() - 1; i > 0; i--)
            {
                values[i - 1] = (vecTmp[i] + (randomValue * values[i]));
            }
            printX(x0);
        }

        complex<double> delta = pow(values[1], 2) - (4.0 * values[2] * values[0]);
        complex<double> x1 = ((-values[1] + sqrt(delta)) / (2.0 * values[2]));
        complex<double> x2 = ((-values[1] - sqrt(delta)) / (2.0 * values[2]));

        print(x1, x2);
    }
};

void printEquation(Laguerr lag, complexVector values, int tab[], int size, bool complex, int t[] = NULL)
{
    for (int i = 0; i < size + 1; i++)
    {
        if (tab[i] != 0)
            cout << tab[i] << "z^" << size - i << " ";

        if (tab[i] == 0)
        {
            cout << t[i] << "iz^" << size - i << " ";
        }
        if (i != size)
        {
            cout << "+ ";
        }
    }
    cout << endl;

    for (int i = size; i >= 0; i--)
    {
        if (complex)
        {
            complexNumber tmp(tab[i], t[i]);
            values.push_back(tmp);
        }
        else
        {
            complexNumber tmp(tab[i], 0);
            values.push_back(tmp);
        }
    }
    
    lag.solve(values);
    values.clear();
}
int main()
{
    Laguerr lag;
    complexVector values;

    int tab[] = {243, -486, 783, -990, 558, -28, -72, 16};
    printEquation(lag, values, tab, 7, false);
    cout << endl;

    int tab2[] = {1, 1, 3, 2, -1, -3, -11, -8, -12, -4, -4};
    printEquation(lag, values, tab2, 10, false);
    cout << endl;

    int tab3a[] = {1, 0, -1, 0, 1};
    int tab3b[] = {0, 1, 0, -1, 0};
    printEquation(lag, values, tab3a, 4, true, tab3b);

    return 0;
}
