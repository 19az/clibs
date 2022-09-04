#!/bin/bash

. ./unit_testing.sh
cd unit_test_c
make
unit_test "test_c.txt" "unit_testing_c_ut" $'<'
cd ../
