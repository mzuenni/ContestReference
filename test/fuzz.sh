#!/bin/bash
set -e
cd "$(dirname "$0")"

while true
do
    seed="0"
    while [[ $seed == 0* ]]; do
        seed=$(tr -dc '0-9' </dev/random |  head -c 18)
    done
    echo "Fuzz using seed: $seed"
    echo
    ./test.sh --seed=$seed "$@"
done
