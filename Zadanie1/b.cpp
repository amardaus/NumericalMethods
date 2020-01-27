//
// Created by olcia on 22.12.2019.
//

#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

using namespace std;

int main() {

    int n = 7;
    gsl_vector *e = gsl_vector_alloc(n);
    gsl_vector *d = gsl_vector_alloc(n);

    gsl_vector *b = gsl_vector_alloc(n);
    gsl_vector *x = gsl_vector_alloc(n);

    for (size_t i = 0; i < n; i++) {
        gsl_vector_set(d, i, 4);
        gsl_vector_set(b, i, i+1);
        gsl_vector_set(e, i, 1);
    }

    gsl_linalg_solve_symm_cyc_tridiag(d, e, b, x);

    for(size_t i=0;i<n;i++){
        cout << "x" << i+1 << " = " << gsl_vector_get(x, i) << endl;
    }

    gsl_vector_free(d);
    gsl_vector_free(e);
    gsl_vector_free(b);
    gsl_vector_free(x);

    return 0;
}