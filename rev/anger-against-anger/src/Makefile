.PHONY: all build clean test
all: build test

build: problem

clean:
	rm encrypt.c problem.c problem problem-debug encrypt 

test: problem
	../dist/problem < flag

problem-debug:  problem.c tiny-AES-c/aes.c keccak-tiny.o
	gcc -std=gnu11 -O1 problem.c tiny-AES-c/aes.c keccak-tiny.o -o problem-debug

problem: problem-debug
	cp problem-debug problem
	strip problem
	upx problem
	bbe -e 's/UPX!/VPX!/' problem > problem_out
	mv problem_out problem
	chmod +x problem

encrypt: encrypt.c tiny-AES-c/aes.c
	gcc -std=c11 encrypt.c tiny-AES-c/aes.c -o encrypt

problem.c: problem.tpl.c generator.py encrypt
	cat flag|wc -m > flag_len
	./encrypt > enc_flag
	python3 generator.py problem.tpl.c enc_flag flag_len > problem.c
	rm enc_flag

encrypt.c: encrypt.tpl.c flag
	python3 generator.py encrypt.tpl.c flag > encrypt.c

keccak-tiny.o: keccak-tiny/keccak-tiny.o
	make -C keccak-tiny/
	cp keccak-tiny/keccak-tiny.o .
