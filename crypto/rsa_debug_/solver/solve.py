from output import N, e, c
from math import isqrt
from Crypto.Util.number import long_to_bytes

square = c*pow(256,-1,N)%N

flag_num = isqrt(square)

print(long_to_bytes(flag_num))
