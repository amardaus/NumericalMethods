#include <iostream>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <iomanip>
#include "alglib/linalg.h"
//
// Created by olcia on 19.12.2019.
//

using namespace std;

constexpr int n = 6;

int main(){
    double A[n][n] = {{19.0/12, 13.0/12, 5.0/6, 5.0/6, 13.0/10, -17.0/12},
                      {13.0/12, 13.0/12, 5.0/6, 5.0/6, -11.0/12, 13.0/12},
                      {5.0/6, 5.0/6, 5.0/6, -1.0/6, 5.0/6, 5.0/6},
                      {5.0/6, 5.0/6, -1.0/6, 5.0/6, 5.0/6, 5.0/6},
                      {13.0/12, -11.0/12, 5.0/6, 5.0/6, 13.0/12, 13.0/12},
                      {-17.0/12, 13.0/12, 5.0/6, 5.0/6, 13.0/12, 19.0/12}};

    gsl_matrix* matrix = gsl_matrix_alloc(n,n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            gsl_matrix_set(matrix, i, j , A[i][j]);
        }
    }

    double tauv[n-1] = {1, 1, 1, 1, 1};
    gsl_vector_view tau = gsl_vector_view_array(tauv, n-1);

    gsl_vector* diagonal = gsl_vector_alloc(n);
    gsl_vector* subdiagonal = gsl_vector_alloc(n-1);

    gsl_linalg_symmtd_decomp(matrix, &tau.vector);
    gsl_linalg_symmtd_unpack_T(matrix, diagonal, subdiagonal);

    for(int i = 0; i < n; i++){
        cout << gsl_vector_get(diagonal,i) << " ";
    }

    cout << endl;
    for(int i = 0; i < n-1; i++){
        cout << setprecision(7) << gsl_vector_get(subdiagonal,i) << " ";
    }
}