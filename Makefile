ftm.out: flighthashtable.o flightticket.o mylist.o main.o 
	g++ flighthashtable.o main.o flightticket.o mylist.o -o ftm.out
main.o: main.cpp
	g++ -c main.cpp
flighthashtable.o: flighthashtable.cpp flighthashtable.h
	g++ -c flighthashtable.cpp
flightticket.o: flightticket.cpp flightticket.h
	g++ -c flightticket.cpp
mylist.o: mylist.cpp mylist.h
	g++ -c mylist.cpp
clean:
	rm *.o *.out
