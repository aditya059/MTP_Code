import numpy as np
from numpy.linalg import inv

M = np.loadtxt("M.txt", dtype='int')

M_inverse = inv(M)

with open('InvM.txt', 'wb') as file:
    for line in M_inverse:
        np.savetxt(file, line, fmt='%f')
