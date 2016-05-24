all: memoriaB_BB.pdf beamerB_BB.pdf

memoriaB_BB.pdf: ./Ejercicios/division.tex ./Ejercicios/tsp.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./memoriaB_BB.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./memoriaB_BB.tex
	make mrproper

beamerB_BB.pdf: ./Ejercicios/divisionMD.tex ./Ejercicios/tspMD.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./beamerB_BB.tex
	pdflatex -shell-escape -interaction=nonstopmode -file-line-error ./beamerB_BB.tex
	make mrproper

mrproper:
	echo "Limpieza"
	find . -regex ".*~" -exec rm -r {} \;

	rm -f ./*.aux
	rm -f ./*.log
	rm -f ./*.nav
	rm -f ./*.out
	rm -f ./*.vrb
	rm -f ./*.snm
	rm -f ./*.toc
	rm -f ./*.gz
