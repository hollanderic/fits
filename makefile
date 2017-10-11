CPPFLAGS:=-std=c++11 -Wall

SRCS:= test.cpp \
	   bayer.cpp \

OBJS = $(subst .cpp,.o,$(SRCS))

%.o: %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

test: $(OBJS)
	g++ -o $@ $^
