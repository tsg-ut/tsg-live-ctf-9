#!/bin/sh

bbe -e 's/VPX!/UPX!/' ../dist/problem > problem_out
mv problem_out problem
upx -d problem
chmod +x problem

