import numpy as np
from numpy.linalg import inv

W = np.loadtxt("W.txt", dtype='int')

W_inverse = inv(W)

with open('InvW.txt', 'wb') as file:
    for line in W_inverse:
        np.savetxt(file, line, fmt='%f')
