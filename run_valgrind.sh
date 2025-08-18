#!/usr/bin/env bash
set -euo pipefail

# Requiere: valgrind

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="$ROOT_DIR/benchmarks/valgrind"
mkdir -p "$OUT_DIR"

echo "==== Recompilando con símbolos (-g) ===="
make -C "$ROOT_DIR/struct_c" clean && make -C "$ROOT_DIR/struct_c"
make -C "$ROOT_DIR/class_cpp" clean && make -C "$ROOT_DIR/class_cpp"

echo "==== Valgrind Memcheck (fugas y errores de memoria) ===="
valgrind --tool=memcheck \
  --leak-check=full --show-leak-kinds=all --track-origins=yes \
  --log-file="$OUT_DIR/memcheck_struct.log" "$ROOT_DIR/struct_c/main" >/dev/null || true

valgrind --tool=memcheck \
  --leak-check=full --show-leak-kinds=all --track-origins=yes \
  --log-file="$OUT_DIR/memcheck_class.log" "$ROOT_DIR/class_cpp/main" >/dev/null || true

echo "==== Valgrind Massif (perfil de heap a lo largo del tiempo) ===="
valgrind --tool=massif --time-unit=ms \
  --massif-out-file="$OUT_DIR/massif_struct.out" "$ROOT_DIR/struct_c/main" >/dev/null || true
ms_print "$OUT_DIR/massif_struct.out" > "$OUT_DIR/massif_struct.txt" || true

valgrind --tool=massif --time-unit=ms \
  --massif-out-file="$OUT_DIR/massif_class.out" "$ROOT_DIR/class_cpp/main" >/dev/null || true
ms_print "$OUT_DIR/massif_class.out" > "$OUT_DIR/massif_class.txt" || true

echo "==== Valgrind DHAT (objetos del heap y lifetimes) ===="
valgrind --tool=dhat --dhat-out-file="$OUT_DIR/dhat_struct.out" "$ROOT_DIR/struct_c/main" >/dev/null || true
valgrind --tool=dhat --dhat-out-file="$OUT_DIR/dhat_class.out" "$ROOT_DIR/class_cpp/main" >/dev/null || true

echo "==== Resumen ===="
echo "Memcheck: $OUT_DIR/memcheck_struct.log y memcheck_class.log"
echo "Massif:   $OUT_DIR/massif_struct.txt y massif_class.txt"
echo "DHAT:     $OUT_DIR/dhat_struct.out y dhat_class.out (ver con dh_view.html si lo deseas)"


