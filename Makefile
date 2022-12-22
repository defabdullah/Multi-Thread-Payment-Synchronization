simulation : main.o 
	g++ -g main.o -o simulation -lpthread

main.o : main.cpp main.h
	g++ -g -c main.cpp

clean:
	rm -f *.o simulation