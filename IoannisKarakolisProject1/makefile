vaccineMonitor: main.o HashModule.o skiplist.o bloomfilter.o mainrelated.o
	g++ --std=c++11  main.o HashModule.o skiplist.o bloomfilter.o mainrelated.o -o vaccineMonitor
main.o :main.cpp  modules.h 
	g++ --std=c++11 -c main.cpp
HashModule.o :HashModule.cpp modules.h
	g++ --std=c++11 -c HashModule.cpp
skiplist.o :skiplist.cpp modules.h
	g++ --std=c++11 -c skiplist.cpp
bloomfilter.o :bloomfilter.cpp modules.h
	g++ --std=c++11 -c bloomfilter.cpp
mainrelated.o :mainrelated.cpp modules.h
	g++ --std=c++11 -c mainrelated.cpp
clean:
	rm vaccineMonitor main.o HashModule.o skiplist.o bloomfilter.o mainrelated.o
