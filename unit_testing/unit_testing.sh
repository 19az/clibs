#!/bin/bash

. ./colorful_printf.sh

function run_test {
    input=$2
    expected=`printf "$3"`
    yellow_printf "Test # $nTest: "
    res=`printf "$input" | ./$1`
    if [ "$res" = "$expected" ]
    then
        green_printf "OK\n\n"
    else
        red_printf "Failed\n\n"
        printf "Args: \n$input\n\n"
        printf "Expected:\n$expected\n\n"
        printf "Result:\n$res\n\n"
        failed_tests+="$nTest "
    fi
    nTest=$(($nTest + 1))
}
failed_tests=""
nTest=1

function unit_test {
    file=$1
    program=$2
    delimiter=$3
    yellow_printf "Unit test for $program\n\n"
    OLD_IFS=$IFS
    IFS=$'\n'
    for test in `cat $file`
    do
        IFS=$delimiter
        run_test $program $test
    done
    IFS=$OLD_IFS
    report
    yellow_printf "Unit test is over\n"
}

function report {
    red_printf "Failed test numbers are: "
    if [ -z "$failed_tests" ]
    then
        red_printf "None"
    else
        red_printf "$failed_tests"
    fi
    printf "\n"
}
