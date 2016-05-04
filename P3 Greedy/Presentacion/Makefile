all: memoriagreedy.tex beamergreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./beamergreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./beamergreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./memoriagreedy.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./memoriagreedy.tex
	echo "Limpieza"
	./.limpieza.sh
