#!/bin/bash
set -e

if [[ "$1" == "--clean" ]]; then
    echo "==== Limpiando compilados y benchmarks ===="
    make -C struct_c clean || true
    make -C class_cpp clean || true
    rm -rf benchmarks
    exit 0
fi

mkdir -p benchmarks

echo "==== Compilando proyectos ===="
make -C struct_c
make -C class_cpp

echo "==== Ejecutando benchmarks C (struct) ===="
./struct_c/main > benchmarks/output_struct.txt
mv results_c.csv benchmarks/results_struct.csv

echo "==== Ejecutando benchmarks C++ (class) ===="
./class_cpp/main > benchmarks/output_class.txt
mv results_cpp.csv benchmarks/results_class.csv

echo "==== Combinando resultados ===="
echo "Implementation,Function,N,Wall_ms,CPU_ms,HeapKB_Delta,RSSKB_Delta" > benchmarks/results_summary.csv
tail -n +2 benchmarks/results_struct.csv >> benchmarks/results_summary.csv
tail -n +2 benchmarks/results_class.csv >> benchmarks/results_summary.csv

echo "==== Benchmarks finalizados ===="
echo "Resultados combinados en benchmarks/results_summary.csv"
