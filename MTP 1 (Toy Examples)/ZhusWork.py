import numpy as np
from numpy import linalg as LA
from numpy.linalg import inv

# Part 1
m = 100000      # No. of Data Points
d = 100         # No. of Features
Name = []       # Name of Person for Part 1
Name1 = []      # Name of Person for Part 2
k = 10
k = int(input("Enter the number of people you want to see "))

DataBase = (np.ceil(np.random.random((m, d)) * 1000) / 10).reshape(m, d)

Query = (np.ceil(np.random.random((1, d)) * 1000) / 10).reshape(1, d)

P_i_square = (LA.norm(DataBase, axis = 1) ** 2).reshape(m, 1)
Q_square = LA.norm(Query) ** 2
Dot_product = (np.dot(DataBase, np.transpose(Query))).reshape(m, 1)

Distance_i = np.subtract(np.add(P_i_square, Q_square), 2 * Dot_product)

for i in range(0, m):
    Name.append([Distance_i[i][0], "Name " + str(i)]) 

Name.sort(key = lambda x: x[0])

print("Top - " + str(k) + " people matching your search without encryption are:")

for i in range(0, k):
    print(Name[i])

# -------------------------------------------------------------------------#
# Part 2
    
epsilon = 10
c = 10
eta = d + 1 + epsilon + c
zero_epsilon = np.zeros((1, epsilon))

# Ephemeral Secrets (beta_Q, v_i, R)
beta_Q = (np.ceil(np.random.random((1, 1)) * 1000) / 10).reshape(1, 1)
#print("Beta_Query Taken = " + str(beta_Q[0][0]))
v_i = (np.ceil(np.random.random((m, epsilon)) * 1000) / 10).reshape(m, epsilon)
R = (np.ceil(np.random.random((1, c)) * 1000) / 10).reshape(1, c)

# Long-Term Secrets (tow, S, M, pi)
tow = (np.ceil(np.random.random((1, c)) * 1000) / 10).reshape(1, c)
tow = np.tile(tow, (m, 1))
S = (np.ceil(np.random.random((1, d + 1)) * 1000) / 10).reshape(1, d + 1)
M = (np.ceil(np.random.random((eta, eta)) * 1000) / 10).reshape(eta, eta)
while (np.linalg.det(M) == 0):
    M = (np.ceil(np.random.random((eta, eta)) * 1000) / 10).reshape(eta, eta)

M_inverse = inv(M).reshape(eta, eta)

# Complete Encryption of DataBase
Encrypted_DataBase = (-(2 * DataBase - S[0][:-1])).reshape(m, d)
Encrypted_DataBase = np.append(Encrypted_DataBase.reshape(m, d), (S[0][d] + P_i_square).reshape(m, 1), axis = 1).reshape(m, d + 1)
Encrypted_DataBase = np.append(Encrypted_DataBase.reshape(m, d + 1), tow.reshape(m, c), axis = 1).reshape(m, d + 1 + c)
Encrypted_DataBase = np.append(Encrypted_DataBase.reshape(m, d + 1 + c), v_i.reshape(m, epsilon), axis = 1).reshape(m, eta)
Encrypted_DataBase = np.dot(Encrypted_DataBase, M_inverse).reshape(m, eta)

# Complete Encryption of Query
Encrypted_Query = np.append(Query, 1).reshape(1, d + 1)
Encrypted_Query = np.append(Encrypted_Query, R, axis = 1).reshape(1, d + 1 + c)
Encrypted_Query = np.append(Encrypted_Query, zero_epsilon, axis = 1).reshape(1, eta)
Encrypted_Query = np.dot(beta_Q, Encrypted_Query).reshape(1, eta)
Encrypted_Query = np.dot(M, np.transpose(Encrypted_Query)).reshape(eta, 1)

Distance_i = np.dot(Encrypted_DataBase, Encrypted_Query).reshape(m, 1)

for i in range(0, m):
    Name1.append([Distance_i[i][0], "Name " + str(i)]) 

Name1.sort(key = lambda x: x[0])

print("Top - " + str(k) + " people matching your search (from encrypted DB and encrypted Query) are:")

for i in range(0, k):
    print(Name1[i])