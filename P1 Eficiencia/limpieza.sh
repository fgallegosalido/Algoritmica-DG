#!/bin/bash
find . -regex ".*~" -exec rm -r {} \;

rm -f ./Presentacion/beamer.aux
rm -f ./Presentacion/beamer.log
rm -f ./Presentacion/beamer.nav
rm -f ./Presentacion/beamer.out
rm -f ./Presentacion/beamer.vrb
rm -f ./Presentacion/beamer.snm
rm -f ./Presentacion/beamer.toc
rm -f ./Presentacion/beamer.synctex.gz
rm -f ./Presentacion/memoria.aux
rm -f ./Presentacion/memoria.log
rm -f ./Presentacion/memoria.out
rm -f ./Presentacion/memoria.synctex.gz
rm -f ./Presentacion/memoria.toc

