# ************Archivo Makefile************
SHELL := /bin/bash

SRC = src
INC = inc
BIN = bin
OBJ = obj

CXX = g++
CXXFLAGS = -std=c++11 -g -I$(INC) -Wall -Wextra -pedantic -Wsign-compare


all : dirs $(BIN)/main


# ************ Compilación de Programa Principal ************
$(BIN)/main: $(OBJ)/main.o $(OBJ)/grafo.o $(OBJ)/insercion.o $(OBJ)/TSP_BB.o $(OBJ)/node.o $(OBJ)/BBtools.o $(OBJ)/point.o
	$(CXX) -o $@ $^

# *********** Compilación de Módulos **************
$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/grafo.h $(INC)/node.h $(INC)/BBtools.h $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/grafo.o: $(SRC)/grafo.cpp $(INC)/grafo.h $(INC)/node.h $(INC)/BBtools.h $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $<  -o $@

$(OBJ)/insercion.o: $(SRC)/insercion.cpp $(INC)/grafo.h $(INC)/node.h $(INC)/BBtools.h $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/TSP_BB.o: $(SRC)/TSP_BB.cpp $(INC)/grafo.h $(INC)/node.h $(INC)/BBtools.h $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/node.o: $(SRC)/node.cpp $(INC)/node.h $(INC)/BBtools.h $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/BBtools.o: $(SRC)/BBtools.cpp $(INC)/BBtools.h $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/point.o: $(SRC)/point.cpp $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $@

#************* Directorios ************
dirs:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)

# ************ Limpieza ************
clean:
	-@rm -rf $(OBJ) $(SRC)/*~ $(INC)/*~ ./*~  2> /dev/null

mrproper: clean
	-@rm -rf $(BIN)
