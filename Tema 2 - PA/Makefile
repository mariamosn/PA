# Maria Moșneag 323CA

CC=g++
CFLAGS=-Wall -Wextra
TARGETS=poduri adrese lego retea

build: $(TARGETS)

run-p1: poduri
	./poduri

run-p2: adrese
	./adrese

run-p3: lego
	./lego

run-p4: retea
	./retea

poduri: poduri.cpp
	$(CC) $(CFLAGS) poduri.cpp -o poduri

adrese: adrese.cpp
	$(CC) $(CFLAGS) adrese.cpp -o adrese

lego: lego.cpp
	$(CC) $(CFLAGS) lego.cpp -o lego

retea: retea.cpp
	$(CC) $(CFLAGS) retea.cpp -o retea

clean:
	rm -f $(TARGETS)
