//
// Created by olcia on 26.12.2019.
//

#include <gsl/gsl_spline.h>
#include <fstream>
#include <iostream>
#include <map>
#include <iomanip>

constexpr int size = 512;

int main(){
    std::string filename = "../Zadanie15/data.txt";
    std::ifstream input;
    input.open(filename);
    int i = 0;
    double* x_arr = new double[size];
    double* y_arr = new double[size];

    if(input.is_open()){
        double val, val2;
        while(input >> val >> val2){
            x_arr[i] = val;
            y_arr[i] = val2;
            i++;
        }
    }
    input.close();

    for(i = 0; i < size; i++){
        //std::cout << std::setprecision(10) << "X: " << x_arr[i] << "\tY: " << y_arr[i] << std::endl;
    }

    gsl_interp_accel* acc = gsl_interp_accel_alloc();
    gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, size);
    gsl_spline_init(spline, x_arr, y_arr, size);


    std::string outputfile = "../Zadanie15/spline.txt";
    std::ofstream output;
    output.open(outputfile);

    for(double xi = x_arr[0]; xi <= x_arr[size-1]; xi += 0.001){
        output << xi << " " << gsl_spline_eval(spline, xi, acc) << "\n";
    }

    output.close();
}
