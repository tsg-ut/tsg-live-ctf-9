from output import N, e, c
from Crypto.Util.number import long_to_bytes

def gcd(a, b):
    if a == 0:
        return b
    while b != 0:
        a, b = b, a % b
    return a

def xgcd(a, b):
    x0, y0, x1, y1 = 1, 0, 0, 1
    while b != 0:
        q, a, b = a // b, b, a % b
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return a, x0, y0

def modinv(a, m):
    g, x, y = xgcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

def solve_p(N, e, c):
    for i in range(1, 100):
        for j in range(1, 100):
            g = abs(gcd(N, pow(i, e, N) * c[0] - pow(j, e, N) * c[1]))
            if g > 1:
                return g

p = solve_p(N, e, c)
q = N // p
phi = (p - 1) * (q - 1)

m = pow(c[-1], modinv(e, phi), N)

for i in range(1, 100):
    for j in range(1, 100):
        now = long_to_bytes((m - i * p - j * q) % N)
        if now[:7] == b'TSGLIVE{'[:7]:
            print(now)
