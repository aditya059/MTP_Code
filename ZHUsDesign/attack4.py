from operator import matmul
import numpy as np
from numpy.linalg import inv

num_of_features = 5

M = np.loadtxt('M.txt', dtype='float')
inv_M = inv(M)

# Assumption: QU have (num_of_features + 1) plaintext [i.e., A and B]
plainDB = np.loadtxt('DataBase.txt', dtype='float')
A = plainDB[0:num_of_features, 0:num_of_features]
B = plainDB[1:num_of_features+1, 0:num_of_features]
C = 2 * np.subtract(A, B)
inv_C = inv(C)

D = np.linalg.norm(A, axis=1)
E = np.linalg.norm(B, axis=1)

F = np.square(D) - np.square(E)

# Assumption: QU have (num_of_features + 1) ciphertext [i.e., encrypted_DB]
DB_cap = np.loadtxt('ModifiedDataBase.txt', dtype='float')
DB_cap = DB_cap[0:num_of_features + 1, 0:]
encrypted_DB = matmul(DB_cap, inv_M)

encrypted_query = np.loadtxt('finalDecryptedQuery.txt', dtype='int')

betaQ = np.gcd.reduce(encrypted_query)

G = np.dot(encrypted_DB, np.transpose(encrypted_query))
G = np.divide(G, betaQ)
H = G[0:num_of_features]
I = G[1:num_of_features + 1]
J = np.subtract(H, I)

K = np.subtract(F, J)

calc_query = np.dot(inv_C, K)
print(calc_query)
