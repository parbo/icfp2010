CC=g++
CCFLAGS=-O2 -msse2 -fomit-frame-pointer -pipe -Wno-deprecated $(CPPFLAGS) -I. -I/usr/local/lib/python2.6/dist-packages/shedskin/lib -D__SS_NOWRAP -D__SS_NOBOUNDS -D__SS_LONG
LFLAGS=-lgc -lpcre $(LDFLAGS)

all:	circuit_shedskin

run:	all
	./circuit_shedskin

CPPFILES=/usr/local/lib/python2.6/dist-packages/shedskin/lib/sys.cpp circuit_shedskin.cpp /usr/local/lib/python2.6/dist-packages/shedskin/lib/builtin.cpp /usr/local/lib/python2.6/dist-packages/shedskin/lib/itertools.cpp /usr/local/lib/python2.6/dist-packages/shedskin/lib/re.cpp
HPPFILES=/usr/local/lib/python2.6/dist-packages/shedskin/lib/sys.hpp circuit_shedskin.hpp /usr/local/lib/python2.6/dist-packages/shedskin/lib/builtin.hpp /usr/local/lib/python2.6/dist-packages/shedskin/lib/itertools.hpp /usr/local/lib/python2.6/dist-packages/shedskin/lib/re.hpp

circuit_shedskin:	$(CPPFILES) $(HPPFILES)
	$(CC)  $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o circuit_shedskin

circuit_shedskin_prof:	$(CPPFILES) $(HPPFILES)
	$(CC) -pg -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o circuit_shedskin_prof

circuit_shedskin_debug:	$(CPPFILES) $(HPPFILES)
	$(CC) -g -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o circuit_shedskin_debug

clean:
	rm -f circuit_shedskin circuit_shedskin_prof circuit_shedskin_debug

.PHONY: all run clean

