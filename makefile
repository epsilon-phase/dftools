CCOPT=-std=c++11 -g 
CC=g++
all: circle sierpinsky htree csv.h concentricity geo_test raw_test reaction_test raw_name_extractor material_test


circle: circle.cpp circle.h csv.h 
	$(CC) $(CCOPT) circle.cpp -o circle

sierpinsky: sierpinsky.cpp csv.h
	$(CC) $(CCOPT) sierpinsky.cpp -o sierpinsky

htree: htree.cpp csv.h
	$(CC) $(CCOPT) htree.cpp -o htree

concentricity:concentricity.cpp circle.h csv.h
	$(CC) $(CCOPT) concentricity.cpp -o concentricity

geo_test: polygon.o shape.o line.o g_circle.o geo_test.cpp clipper.o
	$(CC) $(CCOPT) $(LDOPT) clipper.o polygon.o shape.o line.o g_circle.o geo_test.cpp -o geo_test

polygon.o: polygon.cpp geometry.h
	$(CC) $(CCOPT) -c polygon.cpp

shape.o: shape.cpp geometry.h
	$(CC) $(CCOPT) -c shape.cpp

g_circle.o: g_circle.cpp geometry.h
	$(CC) $(CCOPT) -c g_circle.cpp

line.o: line.cpp geometry.h
	$(CC) $(CCOPT) -c line.cpp
clipper.o:clipper.hpp clipper.cpp
	$(CC) $(CCOPT) -c clipper.cpp
raw_reader.o:raw_reader.cpp raw_reader.hpp
	$(CC) $(CCOPT) -c raw_reader.cpp

raw_test:raw_test.cpp raw_reader.o
	$(CC) $(CCOPT) raw_reader.o raw_test.cpp -o raw_test

reaction.o: raw_reader.o reaction.cpp reaction.hpp
	$(CC) $(CCOPT) -c reaction.cpp
reaction_test:reaction_test.cpp reaction.o
	$(CC) $(CCOPT) reaction.o raw_reader.o reaction_test.cpp -o reaction_test
raw_name_extractor:raw_name_extractor.cpp raw_reader.o
	$(CC) $(CCOPT) raw_name_extractor.cpp raw_reader.o -o raw_name_extractor
dfobject.o:dfobject.cpp dfobject.hpp
	$(CC) $(CCOPT) -c dfobject.cpp
material.o:material.cpp material.hpp dfobject.o
	$(CC) $(CCOPT) -c material.cpp
material_test: material_test.cpp material.o
	$(CC) $(CCOPT) material.o dfobject.o raw_reader.o material_test.cpp -o material_test

doc: Doxyfile *.cpp *.h
	doxygen Doxyfile

clean: 
	rm *.o geo_test htree circle concentricity sierpinsky
