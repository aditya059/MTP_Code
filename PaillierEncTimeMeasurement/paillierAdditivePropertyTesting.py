from phe import paillier

public_key, private_key = paillier.generate_paillier_keypair()
query1 = 5
query2 = 10

encrypted_query1 = public_key.encrypt(query1)
print(encrypted_query1)

encrypted_query2 = public_key.encrypt(query2)
print(encrypted_query2)

encrypted_query1 = encrypted_query1 + encrypted_query2
encrypted_query2 = encrypted_query1 * 10

print(private_key.decrypt(encrypted_query1))
print(private_key.decrypt(encrypted_query2))
