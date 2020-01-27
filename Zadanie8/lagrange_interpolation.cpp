//
// Created by olcia on 25.12.2019.
//
#include <iostream>

double interpolate(double xp, double* x_arr, double* y_arr, int count){
    double result = 0;
    for(int i = 0; i < count; i++){
        double val = y_arr[i];
        for(int j = 0; j < count; j++){
            if(i != j){
                val = val * (xp - x_arr[j])/(x_arr[i] - x_arr[j]);
            }
        }
        result += val;
    }
    return result;
}

int main(){
    double t = 1.0/32;
    int count = 0;

    double x = -1;
    while(x <= 1){
        count ++;
        x += t;
    }

    double* x_arr = new double[count];
    double* y_arr = new double[count];

    x = -1;
    for(int i = 0; i < count; i++){
        x_arr[i] = x;
        y_arr[i] = 1/(1+5*x*x);
        //std::cout << x_arr[i] << " " << y_arr[i] << std::endl;
        x += t;
    }

    for(int i = 0; i < count; i++){
        std::cout << x_arr[i] << " " << interpolate(x_arr[i], x_arr, y_arr, count) << std::endl;
    }
}
