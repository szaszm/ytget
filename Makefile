CPP=clang++
LDFLAGS=-lcurl
#CFLAGS=-I../src/json/src -Wall -Wextra -Werror -O3 -march=native
CFLAGS=-I../src/json/src -Wall -Wextra -Werror -g
CPPFLAGS=-std=c++14

all: youtube_list_playlist youtube_search

clean:
	rm cURL.o HttpResponse.o youtube_search youtube_list_playlist

youtube_list_playlist: youtube_list_playlist.cpp cURL.o HttpResponse.o
	${CPP} -o youtube_list_playlist ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} youtube_list_playlist.cpp cURL.o HttpResponse.o

youtube_search: youtube_search.cpp cURL.o HttpResponse.o
	${CPP} -o youtube_search ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} youtube_search.cpp cURL.o HttpResponse.o

cURL.o: cURL.cpp
	${CPP} -c -o cURL.o ${CPPFLAGS} ${CFLAGS} cURL.cpp

HttpResponse.o: HttpResponse.cpp
	${CPP} -c -o HttpResponse.o ${CPPFLAGS} ${CFLAGS} HttpResponse.cpp


.PHONY: all clean
