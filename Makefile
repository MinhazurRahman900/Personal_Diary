.PHONEY: biuld clean

build: main.c
	gcc -o dairy main.c -s

clean:
	rm dairy
