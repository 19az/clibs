#!/bin/bash

. ./../unit_testing.sh
make
unit_test "test_c.txt" "unit_testing_c_ut" $'<'
