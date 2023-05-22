CC := g++
LDLIBS := -pthread 
CPPFLAGS := -g -I. -Wall
OBJS := Manager.o Puente.o Coche.o

all: Manager

Manager: $(OBJS)
	$(CC) $(LDLIBS) -o Manager $(OBJS)

Manager.o: 
	$(CC) $(CPPFLAGS) -c Manager.cpp

Puente.o: 	
	$(CC) $(CPPFLAGS) -c Puente.cpp

Coche.o: 	
	$(CC) $(CPPFLAGS) -c Coche.cpp

clean:
	rm -rf *~ core Manager $(OBJS)