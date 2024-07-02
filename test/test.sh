#!/bin/bash
set -e
cd "$(dirname "$0")"

find . -type f -name '*.cpp' -print0 | while read -d $'\0' file
do
	echo "${file}:"
    echo "compiling..."
    g++ -std=gnu++17 "${file}" -I ../content/
    echo "running..."
    timeout 10s ./a.out
    echo ""
done

