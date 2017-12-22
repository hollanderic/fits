CPPFLAGS:=-std=c++11 -Wall

SRCS:= test.cpp \
	   bayer.cpp \

OBJS = $(subst .cpp,.o,$(SRCS))

.phony: testapp

%.o: %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

test: $(OBJS)
	g++ -o $@ $^

testapp: fits.cpp test.cpp
	g++ -std=c++11 test.cpp fits.cpp -o testapp