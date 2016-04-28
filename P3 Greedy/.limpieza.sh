#!/bin/bash
find . -regex ".*~" -exec rm -r {} \;

rm -f ./Presentacion/*.aux
rm -f ./Presentacion/*.log
rm -f ./Presentacion/*.nav
rm -f ./Presentacion/*.out
rm -f ./Presentacion/*.vrb
rm -f ./Presentacion/*.snm
rm -f ./Presentacion/*.toc
rm -f ./Presentacion/*.gz
