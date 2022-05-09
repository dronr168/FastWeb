all: fastWeb

fastWeb: build/main.o build/HTTP.o build/spisok.o build/html.o build/noTLS.o build/openssl.o
	g++ -g -pthread build/main.o build/HTTP.o build/spisok.o build/html.o build/noTLS.o build/openssl.o -o build/bin/fastWeb -lssl -lcrypto

build/main.o: main.cpp
	g++ -c main.cpp -o build/main.o

build/HTTP.o: HTTP/HTTP.cpp
	g++ -c HTTP/HTTP.cpp -o build/HTTP.o

build/spisok.o: robots/spisok.cpp
	g++ -c robots/spisok.cpp -o build/spisok.o

build/html.o: html/html.cpp
	g++ -c html/html.cpp -o build/html.o

build/noTLS.o: noTLS.cpp
	g++ -c noTLS.cpp -o build/noTLS.o

build/openssl.o: openssl/openssl.cpp
	g++ -c openssl/openssl.cpp -o build/openssl.o

clean:
	rm build/*.o build/bin/fastWeb
