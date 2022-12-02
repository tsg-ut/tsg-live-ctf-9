.PHONY: all test

all: output.txt test

output.txt: problem.py flag.txt
	python3 problem.py > output.txt

test: output.txt
	head -n3 output.txt > ../solver/output.py
	make -C ../solver
	rm ../solver/output.py
