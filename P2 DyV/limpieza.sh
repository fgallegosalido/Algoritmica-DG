#!/bin/bash
find . -regex ".*~" -exec rm -r {} \;

rm -f ./Presentacion/beamerdyv.aux
rm -f ./Presentacion/beamerdyv.log
rm -f ./Presentacion/beamerdyv.nav
rm -f ./Presentacion/beamerdyv.out
rm -f ./Presentacion/beamerdyv.vrb
rm -f ./Presentacion/beamerdyv.snm
rm -f ./Presentacion/beamerdyv.toc
rm -f ./Presentacion/beamerdyv.synctex.gz
rm -f ./Presentacion/memoriadyv.aux
rm -f ./Presentacion/memoriadyv.log
rm -f ./Presentacion/memoriadyv.out
rm -f ./Presentacion/memoriadyv.synctex.gz
rm -f ./Presentacion/memoriadyv.toc
