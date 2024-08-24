#!/bin/bash
cmake -B build/
cmake --build build/

mkdir -p tests/test_data_tmp