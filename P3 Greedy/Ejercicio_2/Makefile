CXX = g++
CXXFLAGS = -std=c++11
DEF = -D GP_OUT
SRC=./src
BIN=./bin
SCRIPTS=./Scripts
DAT=./datos
GRAF=./graficas



all: datos graficas


graficas: $(SCRIPTS)/*.gp $(DAT)/*.dat
	gnuplot $(SCRIPTS)/visitas_r_fijo.gp
	gnuplot $(SCRIPTS)/visitas_p_fijo.gp
	gnuplot $(SCRIPTS)/tiempo.gp
	gnuplot $(SCRIPTS)/media.gp


datos: $(BIN)/minimizar_visitas $(BIN)/visitas_aleatorias
	$(SCRIPTS)/datos.sh


$(BIN)/minimizar_visitas: $(SRC)/minimizar_visitas.cpp
	$(CXX) $(CXXFLAGS) $(DEF) $^ -o $(BIN)/$@


$(BIN)/visitas_aleatorias: $(SRC)/visitas_aleatorias.cpp
	$(CXX) $(CXXFLAGS) $(DEF) $^ -o $(BIN)/$@
