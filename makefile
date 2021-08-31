programsn:program
	g++  -o "./bin/Secondary"  ./lib/SecondaryNode.o ./lib/SnNode.o -lws2_32
program:common SecondaryNode SnNode MasterNode main
	g++  -o "./bin/Master"  ./lib/MasterNode.o ./lib/common.o ./lib/main.o   -lws2_32
common:
	g++ -std=c++11 -I "../include" -c -o "./lib/common.o" "../src/common.cpp"
SecondaryNode:
	g++ -std=c++11 -I "./include" -c -o "./lib/SecondaryNode.o" "./src/SecondaryNode.cpp"
SnNode:
	g++ -std=c++11 -I "./include" -c -o "./lib/SnNode.o" "./src/SnNode.cpp"
MasterNode:
	g++ -std=c++11 -I "../include" -c -o "./lib/MasterNode.o" "../src/MasterNode.cpp"
main:
	g++ -std=c++11 -I "../include" -c -o "./lib/main.o" "../src/main.cpp"