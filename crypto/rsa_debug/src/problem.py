def my_pow(a, n, m):
    result = 1
    while n > 0:
        if n % 2 != 0:
            result = (result + a) % m # omg! 
        a = (a + a) % m # oops!
        n = n // 2
    return result

from Crypto.Util.number import getPrime, bytes_to_long

p = getPrime(512)
q = getPrime(512)
N = p * q
phi = (p - 1) * (q - 1)
e = 0x101
d = my_pow(e, -1, phi)

with open('flag.txt', 'rb') as f:
    flag = bytes_to_long(f.read())


c = my_pow(flag, e, N)

print(f'N = {N}')
print(f'e = {e}')
print(f'c = {c}')

if my_pow(c, d, N) != flag:
    print('there is a bug i guess lol')
