import numpy as np
import scipy.sparse.linalg as linalg

A = np.array([[2.0, -1.0, 0.0, 0.0, 1.0],
             [-1.0, 2.0, 1.0, 0.0, 0.0],
             [0.0, 1.0, 1.0, 1.0, 0.0],
             [0.0, 0.0, 1.0, 2.0, -1.0],
             [1.0, 0.0, 0.0, -1.0, 2.0]])

eigenvalue, eigenvector = linalg.eigs(A, k = 1, sigma = 0.38197)
print("Eigenvalue: ", eigenvalue)
print("Eigenvector: \n", eigenvector)
