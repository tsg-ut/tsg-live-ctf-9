from Crypto.Util.number import getPrime, bytes_to_long
from random import randint

p = getPrime(2048)
q = getPrime(2048)
N = p * q
e = 65537

with open('flag.txt', 'rb') as f:
    flag = bytes_to_long(f.read())

c = []

for x in range(3):
    m = 0
    for i in range(x // 2):
        m += flag
    for i in range(randint(1, 100)):
        m += p
    for i in range(randint(1, 100)):
        m += q
    c.append(pow(m, e, N))

print(f'N = {N}')
print(f'e = {e}')
print(f'c = {c}')