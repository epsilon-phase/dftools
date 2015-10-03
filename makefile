CCOPT=-std=c++11 -g 
CC=g++
all: circle sierpinsky htree src/csv.h concentricity geo_test raw_test reaction_test raw_name_extractor material_test


circle: src/circle.cpp src/circle.h src/csv.h 
	$(CC) $(CCOPT) src/circle.cpp -o circle

sierpinsky: src/sierpinsky.cpp src/csv.h
	$(CC) $(CCOPT) src/sierpinsky.cpp -o sierpinsky

htree: src/htree.cpp src/csv.h
	$(CC) $(CCOPT) src/htree.cpp -o htree

concentricity:src/concentricity.cpp src/circle.h src/csv.h
	$(CC) $(CCOPT) src/concentricity.cpp -o concentricity

geo_test: polygon.o shape.o line.o  g_circle.o src/geo_test.cpp clipper.o
	$(CC) $(CCOPT) $(LDOPT) clipper.o polygon.o shape.o line.o g_circle.o src/geo_test.cpp -o geo_test

polygon.o: src/polygon.cpp src/geometry.h
	$(CC) $(CCOPT) -c src/polygon.cpp

shape.o: src/shape.cpp src/geometry.h
	$(CC) $(CCOPT) -c src/shape.cpp

g_circle.o: src/g_circle.cpp src/geometry.h
	$(CC) $(CCOPT) -c src/g_circle.cpp

line.o: src/line.cpp src/geometry.h
	$(CC) $(CCOPT) -c src/line.cpp
clipper.o:src/clipper.hpp src/clipper.cpp
	$(CC) $(CCOPT) -c src/clipper.cpp
raw_reader.o:src/raw_reader.cpp src/raw_reader.hpp
	$(CC) $(CCOPT) -c src/raw_reader.cpp

raw_test:src/raw_test.cpp raw_reader.o
	$(CC) $(CCOPT) raw_reader.o src/raw_test.cpp -o raw_test

reaction.o: raw_reader.o src/reaction.cpp src/reaction.hpp
	$(CC) $(CCOPT) -c src/reaction.cpp
reaction_test:src/reaction_test.cpp reaction.o
	$(CC) $(CCOPT) reaction.o raw_reader.o src/reaction_test.cpp -o reaction_test
raw_name_extractor:src/raw_name_extractor.cpp raw_reader.o
	$(CC) $(CCOPT) src/raw_name_extractor.cpp raw_reader.o -o raw_name_extractor
dfobject.o:src/dfobject.cpp src/dfobject.hpp
	$(CC) $(CCOPT) -c src/dfobject.cpp
material.o:src/material.cpp src/material.hpp dfobject.o
	$(CC) $(CCOPT) -c src/material.cpp
material_test: src/material_test.cpp material.o
	$(CC) $(CCOPT) material.o dfobject.o raw_reader.o src/material_test.cpp -o material_test

jsoncpp.o:src/jsoncpp.cpp
	$(CC) $(CCOPT) -c src/jsoncpp.cpp

rewrite:src/rewrite.cpp src/turtle.hpp jsoncpp.o src/csv.h
	$(CC) $(CCOPT) src/rewrite.cpp jsoncpp.o -o rewrite
doc: Doxyfile *.cpp *.h
	doxygen Doxyfile

clean: 
	rm *.o geo_test htree circle concentricity sierpinsky
