import numpy as np
from numpy.linalg import inv

# Part 1
m = 100000              # No. of Documents
n = 100                 # No. of Keywords
Encrypted_File = []    # Encrypted Files for Part 1
Encrypted_File1 = []    # Encrypted Files for Part 2
Encrypted_File2 = []    # Encrypted Files for Part 3
W = []                  # Dictionary
k = 10
k = int(input("Enter the number of papers you want to see "))

for i in range(0, n):
    W.append("Word " + str(i)) 

Index = np.random.choice([0, 1], size=(m,n), p=[9./10, 1./10]).reshape(m, n)

Query = np.random.choice([0, 1], size=(1,n), p=[9./10, 1./10]).reshape(1, n)

Dot_product = (np.dot(Index, np.transpose(Query))).reshape(m, 1)

for i in range(0, m):
    Encrypted_File.append([Dot_product[i][0], "Encrypted File " + str(i)]) 

Encrypted_File.sort(key = lambda x: x[0])

print("Top - " + str(k) + " papers matching your search (Without encryption) are:")

for i in range(0, k):
    print(Encrypted_File[m - i - 1])

# -------------------------------------------------------------------------#
# Part 2 (MSRE - I)
    
# Setup Phase    
S = np.random.choice([0, 1], size=(1,n + 2), p=[1./2, 1./2]).reshape(1, n + 2)

def matrix():
    M = (np.ceil(np.random.random((n + 2, n + 2)) * 1000) / 10).reshape(n + 2, n + 2)
    while (np.linalg.det(M) == 0):
        M = (np.ceil(np.random.random((n + 2, n + 2)) * 1000) / 10).reshape(n + 2, n + 2)
    return M

M1 = matrix()
M1_inverse = inv(M1).reshape(n + 2, n + 2)

M2 = matrix()
M2_inverse = inv(M2).reshape(n + 2, n + 2)

# BuildIndex Phase & Trapdoor Phase
epsilon_i = np.random.random((m, 1)).reshape(m, 1)
#epsilon_i = 0 * epsilon_i
Encrypted_Index = np.append(Index.reshape(m, n), epsilon_i.reshape(m, 1), axis = 1).reshape(m, n + 1)
Encrypted_Index = np.append(Encrypted_Index.reshape(m, n + 1), np.ones((m, 1)).reshape(m, 1), axis = 1).reshape(m, n + 2)

Encrypted_Query = np.append(Query, 1).reshape(1, n + 1)
r = (np.ceil(np.random.random((1, 1)) * 1000) / 10).reshape(1, 1)
#r = r / r
Encrypted_Query = np.dot(r, Encrypted_Query).reshape(1, n + 1)
t = (np.ceil(np.random.random((1, 1)) * 1000) / 10).reshape(1, 1)
#t = 0 * t
Encrypted_Query = np.append(Encrypted_Query.reshape(1, n + 1), t.reshape(1, 1)).reshape(1, n + 2)

Encrypted_Index1 = np.zeros(shape=(m, n + 2))
Encrypted_Index2 = np.zeros(shape=(m, n + 2))
Encrypted_Query1 = np.zeros(shape=(1, n + 2))
Encrypted_Query2 = np.zeros(shape=(1, n + 2))
for i in range(0, n + 2):
    Rand = np.random.random((1, 1)).reshape(1, 1)
    if S[0][i] == 0:
        Encrypted_Index1[:,i] = Encrypted_Index[:,i]
        Encrypted_Index2[:,i] = Encrypted_Index[:,i]
        Encrypted_Query1[0][i] = Rand[0] * Encrypted_Query[0][i]
        Encrypted_Query2[0][i] = (1 - Rand[0]) * Encrypted_Query[0][i]
    else: 
        Encrypted_Index1[:,i] = Rand[0] * Encrypted_Index[:,i]
        Encrypted_Index2[:,i] = (1 - Rand[0]) * Encrypted_Index[:,i]
        Encrypted_Query1[0][i] = Encrypted_Query[0][i]
        Encrypted_Query2[0][i] = Encrypted_Query[0][i]

Encrypted_Index1 = np.dot(Encrypted_Index1, M1)
Encrypted_Index2 = np.dot(Encrypted_Index2, M2)
Encrypted_Query1 = np.dot(M1_inverse, np.transpose(Encrypted_Query1))
Encrypted_Query2 = np.dot(M2_inverse, np.transpose(Encrypted_Query2))

# Query Phase
Dot_product_1 = np.dot(Encrypted_Index1, Encrypted_Query1).reshape(m, 1)
Dot_product_2 = np.dot(Encrypted_Index2, Encrypted_Query2).reshape(m, 1)
Dot_product = np.round(np.add(Dot_product_1, Dot_product_2))

for i in range(0, m):
    Encrypted_File1.append([Dot_product[i][0], "Encrypted File " + str(i)]) 

Encrypted_File1.sort(key = lambda x: x[0])

print("Top - " + str(k) + " papers matching your search (With encrypted Query and encrypted Index) (MSRE - I) are:")

for i in range(0, k):
    print(Encrypted_File1[m - i - 1])


# -------------------------------------------------------------------------#
# Part 3 (MSRE - II)

U = 5
V = 2

# Setup Phase    
S = np.random.choice([0, 1], size=(1, n + U + 1), p=[1./2, 1./2]).reshape(1, n + U + 1)

def matrix():
    M = (np.ceil(np.random.random((n + U + 1, n + U + 1)) * 1000) / 10).reshape(n + U + 1, n + U + 1)
    while (np.linalg.det(M) == 0):
        M = (np.ceil(np.random.random((n + U + 1, n + U + 1)) * 1000) / 10).reshape(n + U + 1, n + U + 1)
    return M

M1 = matrix()
M1_inverse = inv(M1).reshape(n + U + 1, n + U + 1)

M2 = matrix()
M2_inverse = inv(M2).reshape(n + U + 1, n + U + 1)

# BuildIndex Phase & Trapdoor Phase
epsilon_i = np.random.random((m, U)).reshape(m, U)
#epsilon_i = 0 * epsilon_i
Encrypted_Index = np.append(Index.reshape(m, n), epsilon_i.reshape(m, U), axis = 1).reshape(m, n + U)
Encrypted_Index = np.append(Encrypted_Index.reshape(m, n + U), np.ones((m, 1)).reshape(m, 1), axis = 1).reshape(m, n + U + 1)

Vdummy = np.array([0] * (U - V) + [1] * V)
np.random.shuffle(Vdummy)
Encrypted_Query = np.append(Query, Vdummy).reshape(1, n + U)
r = (np.ceil(np.random.random((1, 1)) * 1000) / 10).reshape(1, 1)
#r = r / r
Encrypted_Query = np.dot(r, Encrypted_Query).reshape(1, n + U)
t = (np.ceil(np.random.random((1, 1)) * 1000) / 10).reshape(1, 1)
#t = 0 * t
Encrypted_Query = np.append(Encrypted_Query.reshape(1, n + U), t.reshape(1, 1)).reshape(1, n + U + 1)

Encrypted_Index1 = np.zeros(shape=(m, n + U + 1))
Encrypted_Index2 = np.zeros(shape=(m, n + U + 1))
Encrypted_Query1 = np.zeros(shape=(1, n + U + 1))
Encrypted_Query2 = np.zeros(shape=(1, n + U + 1))
for i in range(0, n + U + 1):
    Rand = np.random.random((1, 1)).reshape(1, 1)
    if S[0][i] == 0:
        Encrypted_Index1[:,i] = Encrypted_Index[:,i]
        Encrypted_Index2[:,i] = Encrypted_Index[:,i]
        Encrypted_Query1[0][i] = Rand[0] * Encrypted_Query[0][i]
        Encrypted_Query2[0][i] = (1 - Rand[0]) * Encrypted_Query[0][i]
    else: 
        Encrypted_Index1[:,i] = Rand[0] * Encrypted_Index[:,i]
        Encrypted_Index2[:,i] = (1 - Rand[0]) * Encrypted_Index[:,i]
        Encrypted_Query1[0][i] = Encrypted_Query[0][i]
        Encrypted_Query2[0][i] = Encrypted_Query[0][i]

Encrypted_Index1 = np.dot(Encrypted_Index1, M1)
Encrypted_Index2 = np.dot(Encrypted_Index2, M2)
Encrypted_Query1 = np.dot(M1_inverse, np.transpose(Encrypted_Query1))
Encrypted_Query2 = np.dot(M2_inverse, np.transpose(Encrypted_Query2))

# Query Phase
Dot_product_1 = np.dot(Encrypted_Index1, Encrypted_Query1).reshape(m, 1)
Dot_product_2 = np.dot(Encrypted_Index2, Encrypted_Query2).reshape(m, 1)
Dot_product = np.round(np.add(Dot_product_1, Dot_product_2))

for i in range(0, m):
    Encrypted_File2.append([Dot_product[i][0], "Encrypted File " + str(i)]) 

Encrypted_File2.sort(key = lambda x: x[0])

print("Top - " + str(k) + " papers matching your search (With encrypted Query and encrypted Index) (MSRE - II) are:")

for i in range(0, k):
    print(Encrypted_File2[m - i - 1])