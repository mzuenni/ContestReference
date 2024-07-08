#!/bin/bash
set -e
cd "$(dirname "$0")"
ulimit unlimited
export MALLOC_PERTURB_="$((2#01011001))"

test_file() {
    echo "$1:"
    echo "compiling..."
    g++ -std=gnu++17 "$1" -I ../content/ -O2 -Wall -Wextra -Wshadow -Werror
    echo "running..."
    timeout 10s ./a.out
    echo ""
}

if [ "$#" -ne 0 ]; then
    for file in "$@"
    do
        test_file $file
    done
else
    find . -type f -name '*.cpp' -print0 | sort -z | while read -d $'\0' file
    do
        test_file $file
    done

    echo "missing tests:"
    find ../content/ -type f -name '*.cpp' -print0 | sort -z | while read -d $'\0' file
    do
        file=${file#../content/}
        if [ ! -f ${file} ]; then
            echo "  ${file}:"
        fi
    done
fi

