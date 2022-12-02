# How to solve
## 1.unpack UPX
In the binary, all "UPX" text is changed to "VPX" so undo it and unpack using [VPX2UPX.sh](VPX2UPX.sh)

## 2.overwrite anti-analysis program
In the extracted binary, there are three anti-analysis program.

1. anti-debugger using self-attach
1. anti-hypervisor using cpuid
1. anti-symbolic-exection using hash function

so overwrite all of them to nop program.

## 3.run solver same as anger
In the end,  rewrite the solver same as anger's one for this problem and run it and you'll get the flag!
