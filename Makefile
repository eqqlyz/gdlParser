all:  gdlParser

gdlParser: Opcodes.o Asm.o BasicBlock.o Cfg.o gdlParser.l
	flex -o gdlParser.cc gdlParser.l
	g++ -o $@ Opcodes.o Asm.o BasicBlock.o Cfg.o gdlParser.cc -lfl -std=c++0x
	rm *.o

Opcodes.o: Opcodes.h Opcodes.cpp
	g++ -c Opcodes.cpp

Asm.o: Asm.h Asm.cpp
	g++ -c Asm.cpp

BasicBlock.o: BasicBlock.h BasicBlock.cpp
	g++ -c BasicBlock.cpp
	
Cfg.o: Cfg.h Cfg.cpp
	g++ -c Cfg.cpp

clean:  
	rm -f gdlParser gdlParser.cc 
