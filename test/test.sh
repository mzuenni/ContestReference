#!/bin/bash
cd "$(dirname "$0")"

g++ -std=gnu++17 template/template.cpp -I ../content/
