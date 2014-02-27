CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=-lcurl -lpthread

all: test_my_curl test_webwx

test_my_curl:
	$(CC) -o test_my_curl.o -c $(CFLAGS) $(CPPPATH) test_my_curl.c
	$(CC) -o my_curl.o -c $(CFLAGS) $(CPPPATH) my_curl.c
	$(CC) -o test_my_curl test_my_curl.o my_curl.o $(LIBPATH) $(LIBS)

test_webwx:                                                                  
	$(CC) -o test_webwx.o -c $(CFLAGS) $(CPPPATH) test_webwx.c
	$(CC) -o webwx.o -c $(CFLAGS) $(CPPPATH) webwx.c
	$(CC) -o my_curl.o -c $(CFLAGS) $(CPPPATH) my_curl.c                    
	$(CC) -o test_webwx test_webwx.o webwx.o my_curl.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test_my_curl test_webwx
