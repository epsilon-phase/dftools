CCOPT=-std=c++11 -g 
CC=g++
all: bin/circle bin/sierpinsky bin/htree bin/concentricity bin/geo_test bin/raw_test bin/reaction_test bin/raw_name_extractor bin/material_test bin/rewrite bin/csv_toppm bin/svg_rewrite


bin/csv_toppm: src/csv_toppm.cpp src/csv.h
	$(CC) $(CCOPT) src/csv_toppm.cpp -o bin/csv_toppm

bin/circle: src/circle.cpp src/circle.h src/csv.h 
	$(CC) $(CCOPT) src/circle.cpp -o bin/circle

bin/sierpinsky: src/sierpinsky.cpp src/csv.h
	$(CC) $(CCOPT) src/sierpinsky.cpp -o bin/sierpinsky

bin/htree: src/htree.cpp src/csv.h
	$(CC) $(CCOPT) src/htree.cpp -o bin/htree

bin/concentricity:src/concentricity.cpp src/circle.h src/csv.h
	$(CC) $(CCOPT) src/concentricity.cpp -o bin/concentricity

bin/geo_test: polygon.o shape.o line.o  g_circle.o src/geo_test.cpp clipper.o
	$(CC) $(CCOPT) $(LDOPT) clipper.o polygon.o shape.o line.o g_circle.o src/geo_test.cpp -o bin/geo_test

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
bin/raw_reader.o:src/raw_reader.cpp src/raw_reader.hpp
	$(CC) $(CCOPT) -c src/raw_reader.cpp

bin/raw_test:src/raw_test.cpp raw_reader.o
	$(CC) $(CCOPT) raw_reader.o src/raw_test.cpp -o raw_test

reaction.o: raw_reader.o src/reaction.cpp src/reaction.hpp
	$(CC) $(CCOPT) -c src/reaction.cpp
bin/reaction_test:src/reaction_test.cpp reaction.o
	$(CC) $(CCOPT) reaction.o raw_reader.o src/reaction_test.cpp -o bin/reaction_test
bin/raw_name_extractor:src/raw_name_extractor.cpp raw_reader.o
	$(CC) $(CCOPT) src/raw_name_extractor.cpp raw_reader.o -o bin/raw_name_extractor
dfobject.o:src/dfobject.cpp src/dfobject.hpp
	$(CC) $(CCOPT) -c src/dfobject.cpp
material.o:src/material.cpp src/material.hpp dfobject.o
	$(CC) $(CCOPT) -c src/material.cpp
bin/material_test: src/material_test.cpp material.o
	$(CC) $(CCOPT) material.o dfobject.o raw_reader.o src/material_test.cpp -o bin/material_test

jsoncpp.o:src/jsoncpp.cpp
	$(CC) $(CCOPT) -c src/jsoncpp.cpp

bin/rewrite:src/rewrite.cpp src/turtle.hpp jsoncpp.o src/csv.h
	$(CC) $(CCOPT) src/rewrite.cpp jsoncpp.o -o bin/rewrite

svg.o:src/svg.hpp src/svg.cpp
	$(CC) $(CCOPT) -c src/svg.cpp

bin/svg_rewrite:src/svg_rewrite.cpp svg.o
	$(CC) $(CCOPT) svg.o jsoncpp.o src/svg_rewrite.cpp -o bin/svg_rewrite

doc: Doxyfile *.cpp *.h
	doxygen Doxyfile

clean: 
	rm *.o bin/*
