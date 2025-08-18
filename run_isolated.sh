#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="$ROOT_DIR/benchmarks/isolated"
mkdir -p "$OUT_DIR"

echo "==== Build harness binaries ===="
make -C "$ROOT_DIR/struct_c" clean && make -C "$ROOT_DIR/struct_c" single
make -C "$ROOT_DIR/class_cpp" clean && make -C "$ROOT_DIR/class_cpp" single

sizes=(10000)

# Funciones C
c_funcs=(findOldest findOldestByCity findRichest findRichestByCity findRichestByGroup listByGroup countByGroup cityWithHighestAvgHeritage percentageOlderThanByGroup netWealthByCity validateTaxGroup)
# Funciones C++ (nombres equivalentes donde cambian)
cpp_funcs=(findOldest findOldestByCity findRichest findRichestByCity findRichestByGroup listTaxGroup countTaxGroup cityWithHighestAvgHeritage percentageOlderThanByGroup netWealthByCity validateTaxGroup)

echo "Implementation,Function,N,Wall_ms,CPU_ms,HeapKB_Delta,RSSKB_Delta" > "$OUT_DIR/results_struct.csv"
echo "Implementation,Function,N,Wall_ms,CPU_ms,HeapKB_Delta,RSSKB_Delta" > "$OUT_DIR/results_class.csv"

for n in "${sizes[@]}"; do
  for func in "${c_funcs[@]}"; do
    for mode in ptr val; do
      "$ROOT_DIR/struct_c/single" --func="$func" --mode="$mode" --n="$n" >> "$OUT_DIR/results_struct.csv"
    done
  done
done

for n in "${sizes[@]}"; do
  for func in "${cpp_funcs[@]}"; do
    for mode in ptr val; do
      "$ROOT_DIR/class_cpp/single" --func="$func" --mode="$mode" --n="$n" >> "$OUT_DIR/results_class.csv"
    done
  done
done

echo "==== Combinando ===="
echo "Implementation,Function,N,Wall_ms,CPU_ms,HeapKB_Delta,RSSKB_Delta" > "$OUT_DIR/results_summary.csv"
tail -n +2 "$OUT_DIR/results_struct.csv" >> "$OUT_DIR/results_summary.csv"
tail -n +2 "$OUT_DIR/results_class.csv" >> "$OUT_DIR/results_summary.csv"

echo "Listo: $OUT_DIR/results_summary.csv"


