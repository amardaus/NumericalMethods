import numpy as np
from scipy.optimize import fsolve


def fun(X):
    x, y = X
    f1 = 2 * x ** 2 + 2 * y ** 2 - 2
    f2 = (x - 0.5) ** 2 + (y - 1) ** 2 - 0.25
    return [f1, f2]


def jac(X):
    x, y = X
    return np.array([
        [4 * x, 2 * y],
        [2 * (x - 0.5), 2 * (y - 1)]])


def close_in(points, point, tol=1e-6):
    nvals = len(points)
    dists = [np.allclose(point, points[cont], atol=tol)
             for cont in range(nvals)]
    return True in dists


npts = 20
tol = 1e-4
np.random.seed(seed=3)
initial_guesses = np.random.uniform(-10, 10, (npts, 2))
sols = []
for x0 in initial_guesses:
    sol, info, ler, msg = fsolve(fun, x0, fprime=jac, full_output=True, xtol=tol)
    if not close_in(sols, sol, tol):
        sols.append(sol)

print(sols[-1])
