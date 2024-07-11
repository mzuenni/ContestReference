#!/bin/bash
set -e
cd "$(dirname "$0")"
ulimit -s unlimited
export MALLOC_PERTURB_="$((2#01011001))"

declare -A cppstandard
cppstandard["string/suffixArray.cpp"]="gnu++20"

test_file() {
    file="${1#./}"
    echo "$file:"
    echo "compiling..."
    std="gnu++17"
    if [[ -v cppstandard[$file] ]]; then
        std=${cppstandard[$file]}
    fi
    g++ -std=$std "$file" -I ../content/ -O2 -Wall -Wextra -Wshadow -Werror
    echo "running..."
    timeout 30s ./a.out
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

    declare -A ignore
    ignore["other/bitOps.cpp"]=1
    ignore["other/compiletime.cpp"]=1
    ignore["other/pbs.cpp"]=1
    ignore["other/pragmas.cpp"]=1
    ignore["other/stuff.cpp"]=1
    ignore["other/timed.cpp"]=1
    ignore["tests/gcc5bug.cpp"]=1
    ignore["tests/precision.cpp"]=1
    ignore["tests/whitespace.cpp"]=1

    echo "missing tests:"
    find ../content/ -type f -name '*.cpp' -print0 | sort -z | while read -d $'\0' file
    do
        file=${file#../content/}
        if [ ! -f $file ] && [[ ! -v ignore[$file] ]]; then
            echo "  $file:"
        fi
    done
fi

