from phe import paillier
import random
import time
d = 100
maxRange = 999999


public_key, private_key = paillier.generate_paillier_keypair()
plaintext = []
for i in range(0, d):
    plaintext.append(random.randint(0, maxRange))

# print(plaintext)
start_time = time.time()
ciphertext = [public_key.encrypt(x) for x in plaintext]
# print(ciphertext)
print(time.time() - start_time)
plaintext = [private_key.decrypt(x) for x in ciphertext]
# print(plaintext)
