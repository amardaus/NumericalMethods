import numpy as np

N = 4

real_matrix = np.array([
    [0, 1, 0, 0],
    [1, 0, 0, 0],
    [0, 0, 0, 1],
    [0, 0, 1, 0],])
imaginary_matrix = np.array([
    [0, 0, 0, -1],
    [0, 0, -1, 0],
    [0, 1, 0, 0],
    [1, 0, 0, 0],
])

imaginary_matrix = imaginary_matrix.astype(complex) * 1j

matrix = real_matrix + imaginary_matrix
#print("Matrix: \n" + str(matrix))

eigenvalues, eigenvectors = np.linalg.eigh(matrix)
print("\nEigenvalues: \n" + str(eigenvalues))

print("\n\n")
for v in eigenvectors:
    print("Eigenvector: " + str(v) + "\n")
