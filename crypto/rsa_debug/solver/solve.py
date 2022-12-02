from output import N, e, c
from math import isqrt
from Crypto.Util.number import long_to_bytes

flag_num = (c-1)*pow(257,-1,N)%N


print(long_to_bytes(flag_num))
