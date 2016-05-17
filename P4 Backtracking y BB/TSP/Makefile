# ************Archivo Makefile************
SHELL := /bin/bash

SRC = src
INC = inc
BIN = bin
OBJ = obj

CXX = g++
CXXFLAGS = -std=c++11 -g -I$(INC)

all : dirs $(BIN)/main

# ************ Compilación de Programa Principal ************
$(BIN)/main : $(OBJ)/main.o $(OBJ)/grafo.o $(OBJ)/insercion.o
	$(CXX) -o $(BIN)/main $(OBJ)/main.o $(OBJ)/grafo.o $(OBJ)/insercion.o

# *********** Compilación de Módulos **************
$(OBJ)/main.o : $(SRC)/main.cpp $(INC)/grafo.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/grafo.o : $(SRC)/grafo.cpp $(INC)/grafo.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/grafo.cpp -o $(OBJ)/grafo.o

$(OBJ)/insercion.o : $(SRC)/grafo.cpp $(INC)/grafo.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/insercion.cpp -o $(OBJ)/insercion.o

$(OBJ)/point.o : $(SRC)/point.cpp
	$(CXX) -c $(CXXFLAGS) $(SRC)/point.cpp -o $(OBJ)/point.o

#************* Directorios ************

dirs :
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)

# ************ Limpieza ************
clean :
	-@rm -rf $(OBJ) $(SRC)/*~ $(INC)/*~ ./*~  2> /dev/null

mrproper : clean
	-@rm -rf $(BIN)
