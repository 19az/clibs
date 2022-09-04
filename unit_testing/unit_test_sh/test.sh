#!/bin/bash

. ./../unit_testing.sh
g++ even.cpp -o even
unit_test "test.txt" "even" $':'
