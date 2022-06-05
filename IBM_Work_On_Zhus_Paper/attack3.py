import numpy as np
from numpy.linalg import inv
num_of_features = 100
c = 2
epsilon = 2
eta = num_of_features + 1 + c + epsilon

# Calculating Encrypted DB Tuple
file = open('ModifiedDataBase.txt')
modified_DB = file.readlines()
modified_tuple1 = [float(x) for x in modified_DB[0].split(" ")[:-1]]
modified_tuple1 = np.array(modified_tuple1)
actual_M = np.loadtxt("M.txt", dtype='int')
M_inverse = inv(actual_M)
encrypted_tuple1 = np.dot(modified_tuple1, M_inverse)
file.close()

# Getting PlainText Query
file = open('DataBase.txt')
DataBase = file.readlines()
plain_tuple1 = [float(x) for x in DataBase[0].split(" ")[:-1]]
for i in range(eta - num_of_features):
    plain_tuple1.append(0.0)
plain_tuple1 = np.array(plain_tuple1)
file.close()

# Performing Attack to get s_vector

plain_tuple1 = np.dot(2, plain_tuple1)
calc_M = np.loadtxt("calcMbyQU.txt", dtype='int')
temp = encrypted_tuple1.dot(calc_M)
s_vector = np.add(plain_tuple1, temp)
np.savetxt('Calculated_s_vector_by_QU.txt', s_vector)

# Performing Attack to get DataBase in clear
modified_DB = np.loadtxt('ModifiedDataBase.txt', dtype='float')
encrypted_DB = np.matmul(modified_DB, M_inverse)

temp = np.matmul(encrypted_DB, calc_M)
temp = temp - s_vector
calc_DB_by_QU = np.divide(temp, -2)
np.savetxt('Calculated_DataBase_by_QU.txt', calc_DB_by_QU)
