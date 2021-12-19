FLAGS = -W -O3

.PHONY = all clean

all: pipe prog1 prog2

pipe: src/pipe.c
	$(CC) $(FLAGS) -o $@ $<
	
prog1: src/prog1.c
	mkdir -p bin
	$(CC) $(FLAGS) -o bin/$@ $<
	
prog2: src/prog2.c
	mkdir -p bin
	$(CC) $(FLAGS) -o bin/$@ $<

clean:
	rm -f bin/prog{1,2} pipe
	rmdir bin
