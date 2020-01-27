//
// Created by olcia on 25.12.2019.
//
#include <iostream>
#include <gsl/gsl_spline.h>
#include <fstream>

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
        //std::cout << i << ": " << y_arr[i] << std::endl;
        x += t;
    }

    gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, count);
    gsl_spline_init(spline, x_arr, y_arr, count);
    gsl_interp_accel* acc = gsl_interp_accel_alloc();

    std::string outputfile = "../Zadanie9/cubicspline.txt";
    std::ofstream output;
    output.open(outputfile);

    for(double xi = x_arr[0]; xi <= x_arr[count-1]; xi += 0.001){
        output << xi << " " << gsl_spline_eval(spline, xi, acc) << "\n";
    }

    output.close();

    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
}
