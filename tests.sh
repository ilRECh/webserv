#!/bin/bash

EXEC=$(realpath webserv)
MAKE=$(dirname $(realpath Makefile))
TEST_SRC=$(realpath ./test)

send_to_server() {
    echo $1 | nc -w $2 localhost $3
}

make_test_build() {
    make -C $MAKE fclean
    make -C $MAKE debug CMDFLAGS+=-DTESTING CMDSRC+=$1
}

##########################################################
# Config testing functions
##########################################################

test_files() {
    if [[ $# < 1 ]]
    then
        return
    fi

    cd $1

    echo "++++++++++++++++++++++++++++++"
    echo "=======>Testing $1<========="
    echo "++++++++++++++++++++++++++++++"
    for TEST in $(ls . | grep ".conf" | sort -n)
    do
        echo
        echo "====>TESTING CONFIG: $(realpath $TEST)<===="
        echo
        $EXEC $TEST
        echo
        echo "========>DONE TESTING<========="
        echo
    done

    cd -
}

config_test() {

    make_test_build $TEST_SRC/config_test.cpp

    if [ -z "$1" ]
    then
        cd config/test
        test_files bad
        test_files good
        test_files .
        cd -
    else
        for CONFIG in "$@"
        do
            echo
            echo "===>TESTING CONFIG: $CONFIG<==="
            echo
            $EXEC $CONFIG
            echo
            echo "========>DONE TESTING<========="
            echo 
        done
    fi
}

server_test() {
    PORT="8888"

    make_test_build $TEST_SRC/server_test.cpp
    $EXEC $PORT & EXEC_PID=$!
    send_to_server "Hello there!" 1 $PORT
    kill -9 $EXEC_PID
}

dispatcher_test() {
    CONF=./config/test/
    PORT_1=7777
    PORT_2=8888
    PORT_3=9999

    make fclean ; make debug
    $EXEC $CONF & EXEC_PID=$!
    send_to_server "Hello first!" 1 $PORT_1 &
    send_to_server "Hello second!" 1 $PORT_2 &
    send_to_server "Hello third!" 1 $PORT_3 &
    sleep 3
    kill -9 $EXEC_PID
}

if  [ "$1" == "config_test" ]
then
    shift
    config_test "$@"
elif [ "$1" == "server_test" ]
then
    shift
    server_test "$@"
elif [ "$1" == "dispatcher_test" ]
then
    shift
    dispatcher_test "$@"
else
    config_test
    server_test
    dispatcher_test
fi


