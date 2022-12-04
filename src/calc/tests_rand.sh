#!/bin/bash
    counter=1
    while [ $counter -le 1000 ]
    do
        ./test_rand
        ((counter++))
    done
    echo All done
