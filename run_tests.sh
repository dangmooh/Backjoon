#!/usr/bin/env bash
EXE="./dp/2293"
TESTS_DIR="./tests"

usage() {
  echo "Usage: $0 [-e exe_path] [-t tests_dir]"
  exit 1
}

while getopts "e:t:" opt; do
  case $opt in
    e) EXE="$OPTARG" ;;
    t) TESTS_DIR="$OPTARG" ;;
    *) usage ;;
  esac
done

if [ ! -d "$TESTS_DIR" ]; then
  echo "Tests directory '$TESTS_DIR' not found. Create tests/ with .in/.out files." >&2
  exit 1
fi

if [ ! -x "$EXE" ]; then
  if [ -x "${EXE}.exe" ]; then
    EXE="${EXE}.exe"
  else
    echo "Executable '$EXE' not found or not executable. Build it first." >&2
    exit 2
  fi
fi

for in in "$TESTS_DIR"/*.in; do
  name=$(basename "$in" .in)
  echo "=== $name ==="
  out=$(cat "$in" | "$EXE")
  expected_file="$TESTS_DIR/$name.out"
  if [ -f "$expected_file" ]; then
    expected=$(cat "$expected_file")
    if [ "$out" = "$expected" ]; then
      echo "PASS"
    else
      echo "FAIL"
      echo "Expected:"; echo "$expected"
      echo "Actual:"; echo "$out"
    fi
  else
    echo "Output:"; echo "$out"
  fi
  echo
done

echo "All tests finished."
