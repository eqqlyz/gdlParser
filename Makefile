all:  gdlParser

gdlParser: gdlParser.l
	flex -o gdlParser.cc gdlParser.l
	g++ -o $@ gdlParser.cc -lfl -std=c++0x

clean:  
	rm -f gdlParser gdlParser.cc 
