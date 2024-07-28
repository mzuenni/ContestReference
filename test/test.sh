#!/bin/bash
set -e
cd "$(dirname "$0")"
ulimit -s 4000000
export MALLOC_PERTURB_="$((2#01011001))"

declare -A cppstandard
cppstandard["string/suffixArray.cpp"]="gnu++20"

test_file() {
    file=$(realpath --relative-to="${PWD}" "${1}")
    echo "$file:"
    echo "compiling..."
    std="gnu++17"
    if [[ -v cppstandard[$file] ]]; then
        std=${cppstandard[$file]}
    fi
    g++ -std=$std "$file" -I ../content/ -O2 -Wall -Wextra -Wshadow -Werror
    echo "running..."
    timeout --foreground 60s ./a.out
    echo ""
    rm ./a.out
}

list_missing() {
    declare -A ignore
    ignore["datastructures/stlPriorityQueue.cpp"]=1
    ignore["datastructures/stlRope.cpp"]=1
    ignore["other/bitOps.cpp"]=1
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
        if [ ! -f "$file" ] && [[ ! -v ignore["$file"] ]]; then
            echo "  $file"
        fi
    done
}

if [ "$#" -ne 0 ]; then
    for arg in "$@"
    do
        if [[ "$arg" == "--missing" ]]; then
            list_missing
        elif [ -d "$arg" ]; then
            dir=$(realpath --relative-to="${PWD}" "$arg")
            find . -type f -path "./${dir}/*.cpp" -print0 | sort -z | while read -d $'\0' file
            do
                test_file "$file"
            done
        elif [ -f "$arg" ]; then
            test_file "$arg"
        fi
    done
else
    find . -type f -path '*.cpp' -print0 | sort -z | while read -d $'\0' file
    do
        test_file "$file"
    done
    list_missing
fi

