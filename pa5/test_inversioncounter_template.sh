#!/bin/bash

################################################################################
# Author  : Ryan Hajtovik
# Version : 1.0
# Date    : March 27, 2025
# Description : Test script to test inversion counter.
# Pledge : I pledge my honor that I have abided by the Stevens Honor System
################################################################################

targetfile=inversioncounter.cpp
cppfile=inversioncounter.cpp
maxtime=8

if [ ! -f "$targetfile" ]; then
    echo "Error: file $targetfile not found"
    echo "Final score: score - penalties = 0 - 0 = 0"
    exit 1
fi

# Required by the Honor System
missing_name=0
head -n 20 "$targetfile" | egrep -i "author.*[a-zA-Z]+"
if [ $? -ne 0 ]; then
    echo "Student name missing"
    missing_name=1
fi

# Required by the Honor System
missing_pledge=0
head -n 20 "$targetfile" | egrep -i "I.*pledge.*my.*honor.*that.*I.*have.*abided.*by.*the.*Stevens.*Honor.*System"
if [ $? -ne 0 ]; then
    echo -e "Pledge missing"
    missing_pledge=1
fi

# Compiling
echo
results=$(make 2>&1)
if [ $? -ne 0 ]; then
    echo "$results"
    echo "Final score: score - penalties = 0 - 0 = 0"
    exit 1
fi

num_tests=0
num_right=0
memory_problems=0
command="./${cppfile%.*}"

run_test_with_args_and_input() {
    ((num_tests++))
    echo -n "Test $num_tests..."

    args="$1"
    input="$2"
    expected_output="$3"

    outputfile=$(mktemp)
    inputfile=$(mktemp)
    statusfile=$(mktemp)

    echo -e "$input" > "$inputfile"

    start=$(date +%s.%N)
    # Run run run, little program!
    (timeout --preserve-status "$maxtime" "$command" $args < "$inputfile" &> "$outputfile"; echo $? > "$statusfile") &> /dev/null
    end=$(date +%s.%N)
    status=$(cat "$statusfile")

    case $status in
        # $command: 128 + SIGBUS = 128 + 7 = 135 (rare on x86)
        135)
            echo "failed (bus error)"
            ;;
        # $command: 128 + SIGSEGV = 128 + 11 = 139
        139)
            echo "failed (segmentation fault)"
            ;;
        # $command: 128 + SIGTERM (sent by timeout(1)) = 128 + 15 = 143
        143)
            echo "failed (time out)"
            ;;
        *)
            # bash doesn't like null bytes so we substitute by hand.
            computed_output=$(sed -e 's/\x0/(NULL BYTE)/g' "$outputfile")
            if [ "$computed_output" = "$expected_output" ]; then
                ((num_right++))
                echo $start $end | awk '{printf "ok (%.3fs)\tvalgrind...", $2 - $1}'
                # Why 93?  Why not 93!
                (valgrind --leak-check=full --error-exitcode=93 $command $args < "$inputfile" &> /dev/null; echo $? > "$statusfile") &> /dev/null
                vgstatus=$(cat "$statusfile")
                case $vgstatus in
                    # valgrind detected an error when running $command
                    93)
                        ((memory_problems++))
                        echo "failed"
                        ;;
                    # valgrind not installed or not in $PATH
                    127)
                        echo "not found"
                        ;;
                    # valgrind: 128 + SIGBUS = 128 + 7 = 135 (rare on x86)
                    135)
                        ((memory_problems++))
                        echo "failed (bus error)"
                        ;;
                    # valgrind: 128 + SIGSEGV = 128 + 11 = 139
                    139)
                        ((memory_problems++))
                        echo "failed (segmentation fault)"
                        ;;
                    # compare with expected status from running $command without valgrind
                    $status)
                        echo "ok"
                        ;;
                    *)
                        ((memory_problems++))
                        echo "unknown status $vgstatus"
                        ;;
                esac
            else
                echo "failed"
                echo "==================== Expected ===================="
                echo "$expected_output"
                echo "==================== Received ===================="
                echo "$computed_output"
                echo "=================================================="
            fi
            ;;
    esac
    rm -f "$inputfile" "$outputfile" "$statusfile"
}

run_test_with_args() {
    run_test_with_args_and_input "$1" "" "$2"
}
run_test_with_input() {
    run_test_with_args_and_input "" "$1" "$2"
}

############################################################
# TODO - Make sure your C++ code can handle these cases.
run_test_with_args_and_input "" "x 1 2 3" "Enter sequence of integers, each followed by a space: Error: Non-integer value 'x' received at index 0."
run_test_with_args_and_input "" "1 2 x 3" "Enter sequence of integers, each followed by a space: Error: Non-integer value 'x' received at index 2."
run_test_with_args_and_input "lots of args" "" "Usage: ./inversioncounter [slow]"
run_test_with_args_and_input "average" "" "Error: Unrecognized option 'average'."
run_test_with_args_and_input "" "" "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."
run_test_with_args_and_input "" "  " "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."

# TODO - write at least 10 extra solid tests that use the "slow" (nested loops) approach. Here is one example.
# You are allowed up to 8 seconds to count inversions on up to 100,000 values.
run_test_with_args_and_input "slow" "2 1" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 1"
run_test_with_args_and_input "slow" "1" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 0"
run_test_with_args_and_input "slow" "" "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."
run_test_with_args_and_input "slow" "1 2 3 4 5" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 0"
run_test_with_args_and_input "slow" "5 4 3 2 1" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 10"
run_test_with_args_and_input "slow" "1 3 2 5 4" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 2"
run_test_with_args_and_input "slow" "1 1 1 1" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 0"
run_test_with_args_and_input "slow" "3 2 1 2 3" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 4"
run_test_with_args_and_input "slow" "100000 99999 99998" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 3"
run_test_with_args_and_input "slow" "7 6 5 4 3 2 1" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 21"
run_test_with_args_and_input "slow" "10 1 2 3 4 5 6 7 8 9" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 9"
run_test_with_args_and_input "slow" "$(seq 100000 | tac | tr '\n' ' ')" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 4999950000"
run_test_with_args_and_input "slow" "$(seq 100000 | tr '\n' ' ')" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 0"
run_test_with_args_and_input "slow" "-3 -2 -1" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 0"
run_test_with_args_and_input "slow" "-1 -2 -3" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 3"
run_test_with_args_and_input "slow" "-3 -2 -1 0 1 2 3" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 0"
run_test_with_args_and_input "slow" "3 2 1 0 -1 -2 -3" "Enter sequence of integers, each followed by a space: Number of inversions (slow): 21"
# END slow tests

maxtime=1
# TODO - write at least 10 extra solid tests that use the fast (MergeSort) approach. Here is one example.
# You are allowed up to 1 second to count inversions on up to 100,000 values.
run_test_with_args_and_input "" "2 1" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 1"
run_test_with_args_and_input "" "1" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 0"
run_test_with_args_and_input "" "1 2 3 4 5" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 0"
run_test_with_args_and_input "" "5 4 3 2 1" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 10"
run_test_with_args_and_input "" "1 3 2 5 4" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 2"
run_test_with_args_and_input "" "1 1 1 1" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 0"
run_test_with_args_and_input "" "3 2 1 2 3" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 4"
run_test_with_args_and_input "" "100000 99999 99998" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 3"
run_test_with_args_and_input "" "7 6 5 4 3 2 1" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 21"
run_test_with_args_and_input "" "10 1 2 3 4 5 6 7 8 9" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 9"
run_test_with_args_and_input "" "$(seq 100000 | tac | tr '\n' ' ')" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 4999950000"
run_test_with_args_and_input "" "$(seq 100000 | tr '\n' ' ')" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 0"
run_test_with_args_and_input "" "-3 -2 -1" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 0"
run_test_with_args_and_input "" "-1 -2 -3" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 3"
run_test_with_args_and_input "" "-3 -2 -1 0 1 2 3" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 0"
run_test_with_args_and_input "" "3 2 1 0 -1 -2 -3" "Enter sequence of integers, each followed by a space: Number of inversions (fast): 21"
# END fast tests
############################################################

echo
echo "Total tests run: $num_tests"
echo "Number correct : $num_right"
score=$((100 * $num_right / $num_tests))
echo "Percent correct: $score%"
if [ $missing_name == 1 ]; then
    echo "Missing Name: -5"
fi
if [ $missing_pledge == 1 ]; then
    echo "Missing or incorrect pledge: -5"
fi

if [ $memory_problems -gt 1 ]; then
    echo "Memory problems: $memory_problems (-5 each, max of -15)"
    if [ $memory_problems -gt 3 ]; then
        memory_problems=3
    fi
fi

penalties=$((5 * $missing_name + 5 * $missing_pledge + 5 * $memory_problems))
final_score=$(($score - $penalties))
if [ $final_score -lt 0 ]; then
    final_score=0
fi
echo "Final score: score - penalties = $score - $penalties = $final_score"

make clean > /dev/null 2>&1
