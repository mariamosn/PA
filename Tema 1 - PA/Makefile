# Maria Moșneag 323CA

CC=g++
CFLAGS=-Wall -Wextra
TARGETS=crypto stocks valley ridge trigigel

build: $(TARGETS)

run-p1: crypto
	./crypto

run-p2: stocks
	./stocks

run-p3: valley
	./valley

run-p4: ridge
	./ridge

run-p5: trigigel
	./trigigel

crypto: crypto.cpp
	$(CC) $(CFLAGS) crypto.cpp -o crypto

stocks: stocks.cpp
	$(CC) $(CFLAGS) stocks.cpp -o stocks

valley: valley.cpp
	$(CC) $(CFLAGS) valley.cpp -o valley

ridge: ridge.cpp
	$(CC) $(CFLAGS) ridge.cpp -o ridge

trigigel: trigigel.cpp
	$(CC) $(CFLAGS) trigigel.cpp -o trigigel

clean:
	rm -f $(TARGETS)
