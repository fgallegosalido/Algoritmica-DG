#!/bin/bash
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./Presentacion/beamergreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./Presentacion/beamergreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./Presentacion/memoriagreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./Presentacion/memoriagreedy.tex
	echo "Errores del grafo:"
	g++ -std=c++11 ./Viajante/grafo.cpp
	echo "Limpieza"
	./.limpieza.sh
