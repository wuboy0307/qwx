CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=-lcurl

all: test_http_get test_webwx

test_http_get:
	$(CC) -o test_http_get.o -c $(CFLAGS) $(CPPPATH) test_http_get.c
	$(CC) -o http_get.o -c $(CFLAGS) $(CPPPATH) http_get.c
	$(CC) -o test_http_get test_http_get.o http_get.o $(LIBPATH) $(LIBS)

test_webwx:                                                                  
	$(CC) -o test_webwx.o -c $(CFLAGS) $(CPPPATH) test_webwx.c
	$(CC) -o webwx.o -c $(CFLAGS) $(CPPPATH) webwx.c
	$(CC) -o http_get.o -c $(CFLAGS) $(CPPPATH) http_get.c                    
	$(CC) -o test_webwx test_webwx.o webwx.o http_get.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test_http_get test_webwx
