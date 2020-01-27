#include <iomanip>
#include <iostream>
//
// Created by olcia on 28.12.2019.
//

constexpr int size = 100;
constexpr float t = 0.01;

using namespace std;
double W[size];
double y,x;

void wk(int N, double *x_arr, int d)
{
    double iloczyn;
    double suma;
    int k = 1;
    while(k <= N)
    {
        W[k] = 0.0;
        for (int i = 1; i <= N-d; i++)
        {
            suma=1.0;
            iloczyn=1.0;
            if(i>=k-d && i<=k)
            {
                for (int j=i; j<=i+d; j++){
                    if(j!=k){
                        iloczyn*=1.0/(x_arr[k]-x_arr[j]);
                    }
                }
                for (int l=i; l>0; l--) {
                    suma *= (-1.0);
                }
                W[k]+=suma*iloczyn;
            }
        }
        k++;
    }
}

double rx(int N, double *x_arr, double *y_arr, double x)
{
    double suma1 = 0.0;
    double suma2 = 0.0;
    for (int i = 1; i <= N; i++)
    {
        suma1+=W[i]/(x-x_arr[i])*y_arr[i];
        suma2+=W[i]/(x-x_arr[i]);
    }
    return y=suma1/suma2;
}

int main()
{
    int n=1;
    int d=3;
    double x_arr[size], y_arr[size];
    
    for (double i = -1.0; i <= 1.0; n++)
    {
        x_arr[n] = i;
        y_arr[n] = 1.0/(1.0+5*i*i);
        i += 1.0/32.0;
    }
    n = n-1;

    int N = n;
    wk(N,x_arr,d);

    for(x = x_arr[1]+t; x < x_arr[N]; x += t)
    {
        for (int i=2; i<=N; i++){
            if(x==x_arr[i]){
                y=y_arr[i];
                break;
            }
        }

        y=rx(N,x_arr,y_arr,x);
        cout <<"\n" << setprecision(5) << x <<" "<< y;
    }
}
