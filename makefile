CCOPT=-std=c++11 -g
CC=g++
all: circle sierpinsky htree csv.h concentricity geo_test


circle: circle.cpp circle.h csv.h 
	$(CC) $(CCOPT) circle.cpp -o circle

sierpinsky: sierpinsky.cpp csv.h
	$(CC) $(CCOPT) sierpinsky.cpp -o sierpinsky

htree: htree.cpp csv.h
	$(CC) $(CCOPT) htree.cpp -o htree

concentricity:concentricity.cpp circle.h csv.h
	$(CC) $(CCOPT) concentricity.cpp -o concentricity

geo_test: polygon.o shape.o line.o g_circle.o geo_test.cpp
	$(CC) $(CCOPT) polygon.o shape.o line.o g_circle.o geo_test.cpp -o geo_test

polygon.o: polygon.cpp geometry.h
	$(CC) $(CCOPT) -c polygon.cpp

shape.o: shape.cpp geometry.h
	$(CC) $(CCOPT) -c shape.cpp

g_circle.o: g_circle.cpp geometry.h
	$(CC) $(CCOPT) -c g_circle.cpp

line.o: line.cpp geometry.h
	$(CC) $(CCOPT) -c line.cpp
