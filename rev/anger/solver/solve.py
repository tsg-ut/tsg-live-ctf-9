#!/usr/bin/env python3
# coding: utf-8
import angr
import claripy

import sys

base_addr=0x400000
if len(sys.argv)>1:
    p = angr.Project(sys.argv[1],auto_load_libs=False,main_opts={'base_addr':base_addr})
else:
    p = angr.Project("../src/problem-debug",auto_load_libs=False,main_opts={'base_addr':base_addr})

input_len = 54
flag_chars = [claripy.BVS('flag_%d' % i, 8) for i in range(input_len)]
flag = claripy.Concat( *flag_chars + [claripy.BVV(b'\n')])

#addr_win=p.loader.find_symbol('win').rebased_addr
addr_win=4617+base_addr

st = p.factory.full_init_state(
    args=['../src/problem-debug'],
    add_options=({
        angr.options.ZERO_FILL_UNCONSTRAINED_MEMORY
    }),
    stdin=flag,
)

for i in range(0,len(flag_chars)-1):
    k=flag_chars[i]
    st.solver.add(k < 0x7f)
    st.solver.add(k >= 0x20)
st.solver.add(flag_chars[0]==ord('T'))
st.solver.add(flag_chars[1]==ord('S'))
st.solver.add(flag_chars[2]==ord('G'))
st.solver.add(flag_chars[3]==ord('L'))
st.solver.add(flag_chars[4]==ord('I'))
st.solver.add(flag_chars[5]==ord('V'))
st.solver.add(flag_chars[6]==ord('E'))
st.solver.add(flag_chars[7]==ord('{'))
st.solver.add(flag_chars[53]==ord('}'))

sm = p.factory.simulation_manager(st)

sm.explore(find=addr_win)

print(sm.found)
print(sm.found[0].posix.dumps(0))
with open('answer','wb') as f:
    f.write(sm.found[0].posix.dumps(0))
