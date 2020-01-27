import numpy as np
from scipy.linalg import eigvalsh_tridiagonal

diagonal = np.array([1.58333, -0.0125957, 2.36902, 0.060241, 1.90646, 1.09354])
subdiagonal = np.array([-2.396467, 0.9347593, -2.078863, 1.177896e-15, -0.2911902])

result = eigvalsh_tridiagonal(diagonal, subdiagonal)
print("Eigenvalues: ", result)

