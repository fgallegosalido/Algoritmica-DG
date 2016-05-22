# ************Archivo Makefile************
SHELL := /bin/bash

SRC = src
INC = inc
BIN = bin
OBJ = obj
LIB = lib

CXX = g++
CXXFLAGS = -std=c++11 -g -I$(INC) -Wall -Wextra -pedantic -Wsign-compare
LIBS = -L$(lib) -lgrafo


all : dirs $(BIN)/main


# ************ Compilación de Programa Principal ************
$(BIN)/main: $(OBJ)/main.o $$(DIR_LIBS)/libgrafo.a
	$(CXX) -o $(BIN)/main $< $(LIBS)


# *********** Compilación de Módulos **************
$(OBJ)/main.o: $(SRC)/main.cpp $(DIR_LIBS)/libgrafo.a
	$(CXX) -c $(CXXFLAGS) $< -o $(OBJ)/main.o $(LIBS)


$(OBJ)/grafo.o: $(SRC)/grafo.cpp $(INC)/grafo.h $(OBJ)/node.o $(OBJ)/insercion.o
	$(CXX) -c $(CXXFLAGS) $< $(OBJ)/insercion.o $(OBJ)/node.o  -o $(OBJ)/grafo.o



$(OBJ)/insercion.o: $(SRC)/insercion.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(OBJ)/BBtools.o: $(SRC)/BBtools.cpp $(INC)/BBtools.h
	$(CXX) -c $(CXXFLAGS) $< -o $(OBJ)/BBtools.o

$(OBJ)/node.o: $(SRC)/node.cpp $(INC)/node.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/node.cpp -o $(OBJ)/node.o

$(OBJ)/point.o: $(SRC)/point.cpp $(INC)/point.h
	$(CXX) -c $(CXXFLAGS) $< -o $(OBJ)/point.o


#************* Bibliotecas ************
$(DIR_LIBS)/libgrafo.a: $(OBJ)/grafo.o $(OBJ)/point.o $(OBJ)/BBtools.o $(OBJ)/node.o $(OBJ)/insercion.o
	$(AR) rvs $@ $^


#************* Directorios ************
dirs:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)

# ************ Limpieza ************
clean:
	-@rm -rf $(OBJ) $(SRC)/*~ $(INC)/*~ ./*~  2> /dev/null

mrproper: clean
	-@rm -rf $(BIN)
