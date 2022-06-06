# References:
# 1. https://discuss.python.org/t/converting-integer-to-byte-string-problem-in-python-3/5058
# 2. https://pycryptodome.readthedocs.io/en/latest/src/examples.html#encrypt-data-with-aes

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import random
import time

d = 1000
maxRange = 999999

plaintext = []

for i in range(0, d):
    plaintext.append(random.randint(0, maxRange))
# print(plaintext)

start_time = time.time()
key = get_random_bytes(16)
ciphertexts = []
nonces = []
tags = []
for i in range(0, d):
    data = bytes(str(plaintext[i]), 'ascii')
    cipher = AES.new(key, AES.MODE_EAX)
    ciphertext, tag = cipher.encrypt_and_digest(data)
    ciphertexts.append(ciphertext)
    tags.append(tag)
    nonces.append(cipher.nonce)
print("Encryption Time = ", time.time() - start_time)

start_time = time.time()

decrypted_texts = []
for i in range(0, d):
    cipher = AES.new(key, AES.MODE_EAX, nonces[i])
    data = cipher.decrypt_and_verify(ciphertexts[i], tags[i])
    decrypted_texts.append(int(data))
print("Decryption Time = ", time.time() - start_time)

# print(decrypted_texts)
